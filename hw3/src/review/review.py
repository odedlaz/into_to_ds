import os
from collections import OrderedDict
import math


class Review(object):
    review_fmt = "{score} qid:{qid} {bag_txt} # {filename}"

    SVM = "svm"
    RAW = "raw"

    # added slots to for attribute access
    # but most importantly - memory saving.
    # there are A LOT of Review objects in memory and this reduced the
    # pressure on memory
    __slots__ = ('path', 'filename', 'terms', 'fileparts')

    def __init__(self, path, terms, fileparts):
        """
        Class that holds needed relevant parameters for each review
        :param path: path to the review
        :param terms: collections.Counter of words in review
        :param fileparts: object that holds the needed-values extracted from file
        """
        self.path = path
        self.filename = os.path.basename(self.path)
        self.terms = terms
        self.fileparts = fileparts

    def __iter__(self):
        """
        Iterates the words in the Review object
        :return: __iter__ of collections.Counter contains the words
        """
        return self.terms.__iter__()

    def format(self, bag_of_words, tfidf=False, format=RAW):
        """
        Sets the format required by arguments, using required defaults.
        :param bag_of_words: dictionary that holds all the words, for vector-scheming
        :param tfidf: Boolean indicates wether to use tfidf or not(=tf)
        :param format: which format to use(defualt is Raw)
        :return: Builds the Review in required format
        """
        if format == Review.SVM:
            return self._format_in_svm_light(bag_of_words, tfidf)

        if format == Review.RAW:
            return self._format_in_raw(bag_of_words, tfidf)

        raise ValueError("format is not supported")

    def _format(self, terms):
        """
        Formats the review using the format needed
        :param terms: Counter holds the words of review
        :return: string in required format.
        """
        bag_txt = " ".join("{}:{}".format(w, data)
                           for w, data in terms.items())

        return self.review_fmt.format(score=self.fileparts.score,
                                      qid=int(self.fileparts.idx),
                                      bag_txt=bag_txt,
                                      filename=self.filename)

    def _generate_tfidf(self, num_of_docs, df):
        """
        Creates tfidf dictionary
        :param num_of_docs: Count of docs
        :param df: df of each word in set
        :return: tfidf dictionary
        """
        return {term: round(tf * math.log(float(num_of_docs) / df[term]), 3)
                for term, tf in self.terms.items()}

    def _format_in_raw(self, bag_of_words, tfidf):
        """
        Creates raw format of reviews
        :param bag_of_words: Dict holds the word
        :param tfidf: Dict with tfidf values
        :return: raw format string
        """
        if not tfidf:
            return self._format(self.terms)

        tfidf_data = self._generate_tfidf(bag_of_words.num_of_docs,
                                          bag_of_words.df)
        return self._format(tfidf_data)

    def _format_in_svm_light(self, bag_of_words, tfidf):
        """
        Creates SVML format of reviews
        :param bag_of_words: Dict holds the word
        :param tfidf: Dict with tfidf values
        :return: SVML format string
        """

        if not tfidf:
            svm_data = OrderedDict(((bag_of_words[w], sum) for w, sum
                                    in sorted(self.terms.items(),
                                              key=lambda x: x[0])))
            return self._format(svm_data)

        tfidf_data = self._generate_tfidf(bag_of_words.num_of_docs,
                                          bag_of_words.df)

        svm_data = OrderedDict(((bag_of_words[w], tfidf) for w, tfidf
                                in sorted(tfidf_data.items(),
                                          key=lambda x: x[0])))
        return self._format(svm_data)

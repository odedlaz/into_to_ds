import os
from collections import OrderedDict
import math


class Review(object):
    review_fmt = "{score} {bag_txt} # {filename}"

    SVM = "svm"
    RAW = "raw"

    # added slots to for attribute access
    # but most importantly - memory saving.
    # there are A LOT of Review objects in memory and this reduced the
    # pressure on memory
    __slots__ = ('path', 'filename', 'terms', 'score')

    def __init__(self, path, terms, score):
        self.path = path
        self.filename = os.path.basename(self.path)
        self.terms = terms
        self.score = score

    def __iter__(self):
        return self.terms.__iter__()

    def format(self, bag_of_words, tfidf=False, format=RAW):
        if format == Review.SVM:
            return self._format_in_svm_light(bag_of_words, tfidf)

        if format == Review.RAW:
            return self._format_in_raw(bag_of_words, tfidf)

        raise ValueError("format is not supported")

    def _format(self, terms):
        bag_txt = " ".join("{}:{}".format(w, data)
                           for w, data in terms.items())

        return self.review_fmt.format(score=self.score,
                                      bag_txt=bag_txt,
                                      filename=self.filename)

    def _generate_tfidf(self, num_of_docs, df):
        return {term: round(tf * math.log(float(num_of_docs) / df[term]), 3)
                for term, tf in self.terms.items()}

    def _format_in_raw(self, bag_of_words, tfidf):
        if not tfidf:
            return self._format(self.terms)

        tfidf_data = self._generate_tfidf(bag_of_words.num_of_docs,
                                          bag_of_words.df)
        return self._format(tfidf_data)

    def _format_in_svm_light(self, bag_of_words, tfidf):

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

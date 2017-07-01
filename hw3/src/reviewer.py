import codecs
import os

from parser import Review, BagOfWords
from utils import ProgressBar


class Reviewer(object):

    @classmethod
    def from_argparse(cls, parser):
            return cls(output_per_dir=parser.generate_per_dir,
                       output_in_svm_light=parser.output_in_svm_light,
                       output_in_tfidf=parser.generate_in_tfidf,
                       words_filter=parser.stopwords,
                       *parser.dirs)

    def __init__(self, *dirs,
                 words_filter=None,
                 output_per_dir=False,
                 output_in_svm_light=False,
                 output_in_tfidf=False):

        self._dirs = dirs

        self._words_filter = words_filter or []

        self._output_per_dir = output_per_dir
        self._output_in_svm_light = output_in_svm_light
        self._output_in_tfdidf = output_in_tfidf

        self._flags = self._get_flags_text()

    def _get_flags_text(self):
        s = 'S' if self._output_per_dir else 's'
        l = 'L' if self._output_in_svm_light else 'l'
        t = 'T' if self._output_in_tfdidf else 't'
        return s + l + t

    def _get_filename(self, dir):
        last_dirs = dir.split(os.sep)[-2:]
        return "{}_{}.txt".format("_".join(last_dirs),
                                  self._flags)

    def write(self, per_dir=False):
        if per_dir:
            self._write_per_dir()
        else:
            self._write_single_file()

    def _write(self, filename, bag_of_words, reviews):

        # get the format of the review
        review_format = Review.RAW
        if self._output_in_svm_light:
            review_format = Review.SVM

        prefix = "writing reviews to disk"
        with ProgressBar(prefix, len(reviews)) as pb:
            with codecs.open(filename, 'w', encoding='utf-8') as f:
                for review in reviews:
                    pb.report()
                    line = review.format(bag_of_words=bag_of_words,
                                         format=review_format,
                                         tfidf=self._output_in_tfdidf)
                    f.write(line + '\n')

    def _write_per_dir(self):
        for dir in map(os.path.abspath, self._dirs):

            bag_of_words = BagOfWords(self._words_filter)
            numoffiles = len(os.listdir(dir))
            filename = self._get_filename(dir)

            reviews = []
            prefix = "crunching reviews for '{}'".format(filename)
            with ProgressBar(prefix, numoffiles) as pb:
                for review in bag_of_words.parse_dir(dir):
                    pb.report()
                    reviews.append(review)

            assert numoffiles == len(reviews)

            self._write(filename, bag_of_words, reviews)

    def _write_single_file(self):
        bag_of_words = BagOfWords(self._words_filter)
        filename = self._get_filename("dataset")
        numoffiles = sum(len(os.listdir(x)) for x in self._dirs)

        reviews = []
        prefix = "crunching reviews for '{}'".format(filename)
        with ProgressBar(prefix, numoffiles) as pb:
            for dir in map(os.path.abspath, self._dirs):
                for review in bag_of_words.parse_dir(dir):
                    pb.report()
                    reviews.append(review)

        assert numoffiles == len(reviews)

        self._write(filename, bag_of_words, reviews)

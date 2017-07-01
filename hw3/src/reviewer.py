import os

from parser import Review, ReviewParser
from utils import ProgressBar


class Reviewer(object):
    def __init__(self, argument_parser):
        self._parser = argument_parser
        self._flags = self._get_flags_text()

    def _get_flags_text(self):
        s = 'S' if self._parser.generate_per_dir else 's'
        l = 'L' if self._parser.output_in_svm_light else 'l'
        t = 'T' if self._parser.generate_in_tfidf else 't'
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

    def _write(self, filename, review_parser, reviews):
        # get the format of the review
        review_format = Review.RAW
        if self._parser.output_in_svm_light:
            review_format = Review.SVM

        # update the bag of words in accordance to the type of the review
        bag = review_parser.bag_of_words
        if review_format == Review.SVM:
            bag = {w: idx + 1 for idx, w
                   in enumerate(sorted(bag))}

        prefix = "writing reviews to disk"
        with ProgressBar(prefix, len(reviews)) as pb:
            with open(filename, 'w') as f:
                for review in reviews:
                    pb.report()
                    line = review.format(bag, review_format)
                    f.write(line + '\n')

    def _write_per_dir(self):
        for dir in map(os.path.abspath, self._parser.dirs):

            review_parser = ReviewParser(self._parser.stopwords)
            numoffiles = len(os.listdir(dir))
            filename = self._get_filename(dir)

            reviews = []
            prefix = "crunching reviews for '{}'".format(filename)
            with ProgressBar(prefix, numoffiles) as pb:
                for review in review_parser.parse_dir(dir):
                    pb.report()
                    reviews.append(review)

            assert numoffiles == len(reviews)

            self._write(filename,
                        review_parser,
                        reviews)

    def _write_single_file(self):
        review_parser = ReviewParser(self._parser.stopwords)
        filename = self._get_filename("dataset")
        numoffiles = sum([len(os.listdir(x)) for x in
                          self._parser.dirs])

        reviews = []
        prefix = "crunching reviews for '{}'".format(filename)
        with ProgressBar(prefix, numoffiles) as pb:
            for dir in map(os.path.abspath, self._parser.dirs):
                for review in review_parser.parse_dir(dir):
                    pb.report()
                    reviews.append(review)

        assert numoffiles == len(reviews)

        self._write(filename,
                    review_parser,
                    reviews)

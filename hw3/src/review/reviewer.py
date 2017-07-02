import codecs
import os

from . import Review
from words_parser import BagOfWordsParser
from collections import defaultdict
from utils import ProgressBar


class Reviewer(object):

    @classmethod
    def from_argparse(cls, parser):
        """
        a constructor that extracts relevant args from an argparse parser
        """
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
        """
        Reviewer is in charge of the whole 'reviewing' process
        it does everything needed to parse files, and dump the processed
        outputs to disk

        :param dirs: a list of directories to go through
        :param words_filter: a list of words to discard when extracting words
        :param output_per_dir: indicates if the output should be per dir or not
        :param output_in_svm_light: indicate if output should be in svm or not
        :param output_in_tfidf: indicate if output should be a sum of tfidf
        """

        self._dirs = dirs

        self._words_filter = words_filter or []

        self._output_per_dir = output_per_dir
        self._output_in_svm_light = output_in_svm_light
        self._output_in_tfdidf = output_in_tfidf

    @staticmethod
    def _get_flags_text(out_per_dir, svm_light_format, out_in_tfidf):
        """
        get flags text in 'slt' format
        """
        s = 'S' if out_per_dir else 's'
        l = 'L' if svm_light_format else 'l'
        t = 'T' if out_in_tfidf else 't'
        return s + l + t

    @staticmethod
    def _get_filename(dir, flags):
        """
        create the filename of directory with the run flags
        """
        last_dirs = dir.split(os.sep)[-2:]
        return "{}_{}.txt".format("_".join(last_dirs), flags)

    def write(self):
        """
        perform all the logic - crunch data and write to disk.
        """
        if self._write_per_dir:
            return self._write_per_dir()

        return self._write_single_file()

    def _write(self, filename, bag_of_words, reviews):
        """
        write reviews to disk
        :param filename: the filename to write the output to
        :param bag_of_words: an instance of BagOfWordsParser
        :param reviews: all the reviews to write to disk
        """

        # get the format of the review
        review_format = Review.RAW
        if self._output_in_svm_light:
            review_format = Review.SVM

        prefix = "writing '{}' reviews to disk".format(filename)
        with ProgressBar(prefix, len(reviews)) as pb:
            with codecs.open(filename, 'w', encoding='utf-8') as f:
                for review in reviews:
                    pb.report()
                    line = review.format(bag_of_words=bag_of_words,
                                         format=review_format,
                                         tfidf=self._output_in_tfdidf)
                    f.write(line + '\n')

    def _write_per_dir(self):
        """
        write outputs of each directory to a different file
        """

        bag_of_words = BagOfWordsParser(self._words_filter)
        reviews_per_dir = defaultdict(list)

        flags = Reviewer._get_flags_text(self._output_per_dir,
                                         self._output_in_svm_light,
                                         self._output_in_tfdidf)

        for dir in map(os.path.abspath, self._dirs):
            numoffiles = len(os.listdir(dir))
            filename = Reviewer._get_filename(dir, flags)

            reviews = reviews_per_dir[filename]
            prefix = "crunching reviews for '{}'".format(filename)

            with ProgressBar(prefix, numoffiles) as pb:
                for review in bag_of_words.parse_dir(dir):
                    pb.report()
                    reviews.append(review)

            assert numoffiles == len(reviews)

        # we update here because the bag of words is not updated yet
        # when we're still reading the files in the directories
        for filename, reviews in reviews_per_dir.items():
            self._write(filename, bag_of_words, reviews)

    def _write_single_file(self):
        """
        write outputs of all directory to one file
        """
        bag_of_words = BagOfWordsParser(self._words_filter)
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

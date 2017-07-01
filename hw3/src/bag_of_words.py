import argparse
import os
import sys

import argparse_actions as actions
from parser import Review, ReviewParser
from utils import ProgressBar


def parse_arguments(args=None):
    parser = argparse.ArgumentParser(description='Bag of Words')

    parser.add_argument('dirs',
                        metavar='DIR',
                        action=actions.ValidateDirectoriesAction,
                        nargs='+',
                        help='directories that contain reviews')

    current_file_dir = os.path.dirname(os.path.abspath(__file__))
    parser.add_argument('--stopwords',
                        default=os.path.join(current_file_dir,
                                             "stopwords.txt"),
                        action=actions.LoadStopWordsAction,
                        help='path to a stopwords file')

    parser.add_argument('-t',
                        dest='generate_in_tfidf',
                        action='store_true',
                        default=False,
                        help='generate tfidf representation for each review',
                        required=False)

    parser.add_argument('-s',
                        default=False,
                        action='store_true',
                        dest='generate_per_dir',
                        help='generate output per directory',
                        required=False)

    parser.add_argument('-l',
                        dest='output_in_svm_light',
                        action='store_true',
                        default=False,
                        help='generate output in svm light format',
                        required=False)

    return parser.parse_args(args or sys.argv[1:])


def get_flags_text(parser):
    s = 'S' if parser.generate_per_dir else 's'
    l = 'L' if parser.output_in_svm_light else 'l'
    t = 'T' if parser.generate_in_tfidf else 't'
    return s + l + t


def get_results_filename(flags, dir, ext=""):
    last_dirs = dir.split(os.sep)[-2:]
    return "{}_{}.txt".format("_".join(last_dirs), flags)


def generate_output_file_per_directory(argument_parser):
    for dir in map(os.path.abspath, argument_parser.dirs):
        review_parser = ReviewParser(argument_parser.stopwords)
        numoffiles = len(os.listdir(dir))
        filename = get_results_filename(flags, dir)
        prefix = "crunching reviews for '{}'".format(filename)
        reviews = []

        with ProgressBar(prefix, numoffiles) as pb:
            for review in review_parser.parse_dir(dir):
                pb.report()
                reviews.append(review)

        bag = review_parser.bag_of_words
        if review_format == Review.SVM:
            bag = {w: idx + 1 for idx, w
                   in enumerate(sorted(bag))}

        prefix = "writing reviews to disk"

        assert numoffiles == len(reviews)

        with ProgressBar(prefix, numoffiles) as pb:
            with open(filename, 'w') as f:
                for review in reviews:
                    pb.report()
                    line = review.format(bag, review_format)
                    f.write(line + '\n')


def generate_single_output_file(argument_parser):
    review_parser = ReviewParser(argument_parser.stopwords)
    numoffiles = sum([len(os.listdir(x)) for x in
                      argument_parser.dirs])
    filename = get_results_filename(flags, "dataset")
    prefix = "crunching reviews for '{}'".format(filename)
    reviews = []

    with ProgressBar(prefix, numoffiles) as pb:
        for dir in map(os.path.abspath, argument_parser.dirs):
            for review in review_parser.parse_dir(dir):
                pb.report()
                reviews.append(review)

    bag = review_parser.bag_of_words
    if review_format == Review.SVM:
        bag = {w: idx + 1 for idx, w
               in enumerate(sorted(bag))}

    prefix = "writing reviews to disk"

    assert numoffiles == len(reviews)

    with ProgressBar(prefix, numoffiles) as pb:
        with open(filename, 'w') as f:
            for review in reviews:
                pb.report()
                line = review.format(bag, review_format)
                f.write(line + '\n')


if __name__ == "__main__":
    argument_parser = parse_arguments()

    review_format = Review.RAW
    if argument_parser.output_in_svm_light:
        review_format = Review.SVM

    flags = get_flags_text(argument_parser)

    if argument_parser.generate_per_dir:
        generate_output_file_per_directory(argument_parser)
    else:
        generate_single_output_file(argument_parser)

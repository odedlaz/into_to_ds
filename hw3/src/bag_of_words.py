import argparse
import sys
import os
from parser import ReviewParser, Review
from argparse_actions import ValidateDirectoriesAction, LoadStopWordsAction
import itertools
CURRENT_FILE_DIR = os.path.dirname(os.path.abspath(__file__))


def parse_arguments(args=None):
    parser = argparse.ArgumentParser(description='Bag of Words')

    parser.add_argument('dirs',
                        metavar='DIR',
                        action=ValidateDirectoriesAction,
                        nargs='+',
                        help='put something here please')

    parser.add_argument('--stopwords',
                        default=os.path.join(CURRENT_FILE_DIR,
                                             "stopwords.txt"),
                        action=LoadStopWordsAction,
                        help='path to a stopwords file')

    parser.add_argument('-t',
                        type=bool,
                        default=False,
                        help='generate tfidf representation for each review',
                        required=False)

    parser.add_argument('-s',
                        type=bool,
                        default=False,
                        help='generate output per directory',
                        required=False)

    parser.add_argument('-l',
                        type=bool,
                        default=False,
                        help='generate output in svm light format',
                        required=False)

    return parser.parse_args(args or sys.argv[1:])


if __name__ == "__main__":
    argument_parser = parse_arguments()
    review_parser = ReviewParser(argument_parser.stopwords)

    assert 'too' not in argument_parser.stopwords

    # load all the reviews
    # make sure they are all consumed so the parser will have an updated bag
    reviews = list(itertools.chain(*(review_parser.parse_dir(dir)
                                     for dir in argument_parser.dirs)))

    # get the unsorted and sorted bag of words
    bag = review_parser.bag_of_words
    sorted_bag = review_parser.sorted_bag_of_words

    for review in reviews:
        print(review.format_review(bag))
        print(review.format_review(sorted_bag,
                                   format=Review.SVM))

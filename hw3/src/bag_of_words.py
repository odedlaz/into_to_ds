import argparse
import os
import sys

import argparse_actions as actions
from reviewer import Reviewer


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


if __name__ == "__main__":
    argument_parser = parse_arguments()
    reviewer = Reviewer.from_argparse(argument_parser)
    reviewer.write(per_dir=argument_parser.generate_per_dir)

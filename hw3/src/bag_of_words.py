import argparse
import sys
import os
import nltk
from parser import ReviewParser, Review

CURRENT_FILE_DIR = os.path.dirname(os.path.abspath(__file__))


class ValidateDirectoriesAction(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):

        error_fmt = "'{}' dir doesn't exist"
        for dir in values:
            if not os.path.isdir(dir):
                raise argparse.ArgumentError(self, error_fmt.format(dir))

        namespace.dirs = values


def load_stopwords(path):
    # we've taken lab9's stop words file, and combined it with nltk's
    # how? we wrote nltk's to disk, added to lab9's, and cleaned duplicates.

    # if the file doesn't exist for some reason, fallback to ntlk's corpus
    if os.path.isfile(path):
        with open(path, "r") as f:
            return [x.strip() for x in f.readlines()]

    try:
        return nltk.corpus.stopwords.words('english')
    except LookupError:
        msg = 'stopwords file is missing, and nltk corpus is not installed'
        raise argparse.ArgumentTypeError(msg)


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
                        type=load_stopwords,
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
    parser = parse_arguments()
    review_parser = ReviewParser(parser.stopwords)

    reviews = []
    for dir in parser.dirs:
        for p in review_parser.parse_dir(dir):
            reviews.append(p)

    bag = review_parser.bag_of_words
    sorted_bag = review_parser.sorted_bag_of_words

    for p in reviews:
        print(p.format_review(bag))
        print(p.format_review(sorted_bag,
                              format=Review.SVM))

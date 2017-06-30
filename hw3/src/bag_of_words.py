import argparse
import sys
import os
import re
from collections import Counter, OrderedDict
import nltk

# we use beautiful soup to remove html tags from the code
# nltk dropped support for cleaning html in favor of BeatifulSoup:
# https://stackoverflow.com/q/26002076
from bs4 import BeautifulSoup


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


class Review(object):
    review_fmt = "{score} {bag_txt} # {filename}"

    SVM = "svm"
    RAW = "raw"

    def __init__(self, filename, words, score):
        self.filename = filename
        self.words = words
        self.score = score

    def format_review(self, bag_of_words, format=RAW):
        if format == Review.SVM:
            return self._format_in_svm_light(bag_of_words)

        if format == Review.RAW:
            return self._format_in_raw(bag_of_words)

        raise ValueError("format is not supported")

    def _format(self, words, bag_of_words):
        bag_txt = " ".join("{}:{}".format(w, sum)
                           for sum, w in words)
        return self.review_fmt.format(score=self.score,
                                      bag_txt=bag_txt,
                                      filename=self.filename)

    def _format_in_raw(self, bag_of_words):
        return self._format(self.words.items(), bag_of_words)

    def _format_in_svm_light(self, bag_of_words):
        svm_data = [(self.words[w], idx + 1) for idx, (w, _)
                    in enumerate(bag_of_words.items())
                    if w in self.words]

        return self._format(svm_data, bag_of_words)


class ReviewParser(object):

    filename_re = re.compile('(?P<idx>.*)_(?P<score>.*)\.(?P<ext>.*)')

    def __init__(self, words_filter=None):
        self._words_filter = words_filter or []
        self._bag_of_words = Counter()

    def parse_dir(self, dir):
        for filename in os.listdir(dir):
            path = os.path.join(dir, filename)
            yield self.parse_file(path)

    def _parse_filename(self, filename):
        m = self.filename_re.match(filename)
        if not m:
            raise ValueError("filename is not in the correct format")
        return m.groupdict()

    def parse_file(self, path):
        filename = os.path.basename(path)
        score = self._parse_filename(filename)['score']

        with open(path, 'r') as f:
            txt = f.read().lower()
            file_bag_of_words = Counter(self._get_words(txt))
            self._bag_of_words.update(file_bag_of_words)
            return Review(score=score,
                          words=file_bag_of_words,
                          filename=filename)

    def _get_words(self, txt):
        soup = BeautifulSoup(txt, "html.parser")
        tokens = nltk.wordpunct_tokenize(soup.get_text())
        for word in filter(str.isalpha, nltk.Text(tokens)):
            # words should have at least two characters
            if len(word) <= 1 or word in self._words_filter:
                continue
            yield word

    @property
    def bag_of_words(self):
        return dict(self._bag_of_words)

    @property
    def sorted_bag_of_words(self):
        return OrderedDict(sorted(self._bag_of_words.items(),
                                  key=lambda x: x[0]))


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

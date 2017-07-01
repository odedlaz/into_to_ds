import os
import re
from collections import Counter, OrderedDict

import nltk
# we use beautiful soup to remove html tags from the code
# nltk dropped support for cleaning html in favor of BeatifulSoup:
# https://stackoverflow.com/q/26002076
from bs4 import BeautifulSoup

CURRENT_FILE_DIR = os.path.dirname(os.path.abspath(__file__))


class Review(object):
    review_fmt = "{score} {bag_txt} # {filename}"

    SVM = "svm"
    RAW = "raw"

    def __init__(self, path, words, score):
        self.path = path
        self.filename = os.path.basename(self.path)
        self.words = words
        self.score = score

    def format(self, bag_of_words, format=RAW):
        if format == Review.SVM:
            return self._format_in_svm_light(bag_of_words)

        if format == Review.RAW:
            return self._format_in_raw(bag_of_words)

        raise ValueError("format is not supported")

    def _format(self, words):
        bag_txt = " ".join("{}:{}".format(w, sum)
                           for w, sum in words)

        return self.review_fmt.format(score=self.score,
                                      bag_txt=bag_txt,
                                      filename=self.filename)

    def _format_in_raw(self, bag_of_words):
        return self._format(self.words.items())

    def _format_in_svm_light(self, bag_of_words):
        svm_data = OrderedDict(((bag_of_words[w], sum) for w, sum
                                in sorted(self.words.items(),
                                          key=lambda x: x[0])))

        return self._format(svm_data.items())


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
                          path=path)

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
        return self._bag_of_words.keys()

    @property
    def sorted_bag_of_words(self):
        return sorted(self.bag_of_words)

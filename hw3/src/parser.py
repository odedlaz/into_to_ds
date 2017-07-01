import codecs
import os
import re
from collections import Counter, namedtuple
from review import Review
import nltk
# nltk dropped support for cleaning html in favor of BeatifulSoup:
# https://stackoverflow.com/q/26002076
# we use beautiful soup to remove html tags from the code
# it is part of anaconda, so no installation is needed
from bs4 import BeautifulSoup

FileParts = namedtuple('FileParts', ['idx', 'score', 'ext'])


class BagOfWords(object):

    filename_re = re.compile('(?P<idx>.*)_(?P<score>.*)\.(?P<ext>.*)')

    # After searching through the net, we learned that in general
    # porter2 (snowball) is the best overall stemming algorithm,
    # but not necessarily the fastest or most aggressive.
    stemmer = nltk.SnowballStemmer('english')

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

        return FileParts(**m.groupdict())

    def parse_file(self, path):
        filename = os.path.basename(path)

        fileparts = self._parse_filename(filename)

        with codecs.open(path, 'r', encoding='utf-8') as f:
            txt = f.read().lower()
            file_bag_of_words = Counter(self._get_words(txt))
            self._bag_of_words.update(file_bag_of_words)
            return Review(score=fileparts.score,
                          words=file_bag_of_words,
                          path=path)

    def _get_words(self, txt):
        soup = BeautifulSoup(txt, "html.parser")
        tokens = nltk.wordpunct_tokenize(soup.get_text())
        for word in filter(str.isalpha, nltk.Text(tokens)):
            # words should have at least two characters
            # and should not belong to the word filter
            if len(word) > 1 and word not in self._words_filter:
                yield self.stemmer.stem(word)

    @property
    def bag_of_words(self):
        return self._bag_of_words.keys()

    def __iter__(self):
        return self.bag_of_words.__iter__()

import codecs
import os
import re
from collections import Counter, defaultdict, namedtuple

import nltk

# nltk dropped support for cleaning html in favor of BeatifulSoup:
# https://stackoverflow.com/q/26002076
# we use beautiful soup to remove html tags from the code
# it is part of anaconda, so no installation is needed
from bs4 import BeautifulSoup

from review import Review

FileParts = namedtuple('FileParts', ['idx', 'score', 'ext'])


class BagOfWordsParser(object):

    filename_re = re.compile('(?P<idx>.*)_(?P<score>.*)\.(?P<ext>.*)')

    # After searching through the net, we learned that in general
    # porter2 (snowball) is the best overall stemming algorithm,
    # but not necessarily the fastest or most aggressive.
    stemmer = nltk.SnowballStemmer('english')

    def __init__(self, words_filter=None):
        """
        BagOfWordsParser is in charge of parsing files
        and providing means to get various statistics and data on the terms
        it has come across when parsing these files

        :param words_filter: a list of words to discard when crunching data
        """
        self._words_filter = words_filter or []
        self._bag_of_words = set()
        self._terms_to_index = {}
        self.df = defaultdict(int)
        self.num_of_docs = 0

    def parse_dir(self, dir):
        """
        parses a directory
        :param dir: the directory to parse
        :return: a generator with all the extracted Review objects
        """
        for filename in os.listdir(dir):
            path = os.path.join(dir, filename)
            yield self.parse_file(path)

    def _parse_filename(self, filename):
        """
        parses a file from a given path
        :param filename: the name of a file, including extension
        :return: a FileParts object
        """
        m = self.filename_re.match(filename)

        if not m:
            raise ValueError("filename is not in the correct format")

        return FileParts(**m.groupdict())

    def parse_file(self, path):
        """
        parses a file from a given path
        :param path: a path to a file
        :return: a Review object of file
        """
        self.num_of_docs += 1

        filename = os.path.basename(path)
        fileparts = self._parse_filename(filename)

        with codecs.open(path, 'r', encoding='utf-8') as f:
            txt = f.read()
            terms = Counter(self._get_words(txt))
            self._bag_of_words.update(terms)
            self._terms_to_index.clear()

            # sum the number of documents that contain the term
            for term in terms:
                self.df[term] += 1

            return Review(fileparts=fileparts,
                          terms=terms,
                          path=path)

    def _get_words(self, txt):
        """
        parses a text and returns words after:
            - converting to lowercase
            - removing stop words
            - performing stemming
        """
        soup = BeautifulSoup(txt.lower(), "html.parser")
        tokens = nltk.wordpunct_tokenize(soup.get_text())
        for word in filter(str.isalpha, nltk.Text(tokens)):
            # words should have at least two characters
            # and should not belong to the word filter
            if word not in self._words_filter:
                yield self.stemmer.stem(word)

    def __getitem__(self, term):
        """
        an implementation for an indexer for a term
        :param term: the term to return
        :return: the index from a sorted list of all terms
        """
        if not self._terms_to_index:
            self._terms_to_index = {w: idx + 1 for idx, w
                                    in enumerate(sorted(self))}

        return self._terms_to_index.__getitem__(term)

    @property
    def terms(self):
        """
        a property that returns an immutable list of the words
        """

        # the returned terms should be immutable
        # so we're copying the set to make sure it can't be altered
        # from the outside
        return list(self._bag_of_words)

    def __len__(self):
        """
        implements len for the terms
        """
        return self._bag_of_words.__len__()

    def __iter__(self):
        """
        implements an iterator for the terms
        """
        return self._bag_of_words.__iter__()

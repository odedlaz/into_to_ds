import math
import re
from collections import Counter

from consts import BOOLEAN, TF, TFIDF
from utils import get_empty_vec

punctuation_marks = ["", ".", ",", "?", "!",
                     ";", ":", "-",
                     "[", "]",
                     "(", ")",
                     "{", "}",
                     "'", '"', "*"]

puncs_pattern = "[%s]" % re.escape("".join(punctuation_marks))


class FileReader(object):
    def __init__(self, filepath, words_filter=None, vector_type=BOOLEAN):

        if vector_type not in (BOOLEAN, TF, TFIDF):
            raise ValueError("vector type is not supported")

        self._filepath = filepath
        self._vector_type = vector_type
        self._df = {}

        self._words_filter = set(map(str.lower, words_filter or []))
        self._puncs_re = re.compile(puncs_pattern, re.IGNORECASE)

        self._words = self._get_word_bank()

    def _get_clean_words(self, line):
        """
        get a generator of words in a line, excluding:
            - punctuation marks
            - filtered words
        """
        # remove punctuation marks from line
        stripped_line = self._puncs_re.sub("", line.strip())

        # yield words that shouldn't be filtered
        for word in map(str.lower, stripped_line.split(" ")):
            if word in self._words_filter:
                continue

            yield word

    def _get_word_index(self, word):
        """
        get the index of a given word
        """
        return self._words[word] - 1

    def _get_word_bank(self):
        # starting with 1 because 0 cant serve as a dictionary key
        index, words = 1, {}

        with open(self._filepath, 'r') as f:
            for raw_line in f:
                line = raw_line[:raw_line.index("\t")]
                for word in self._get_clean_words(line):
                    # if the word already exists -> discard it
                    if word in words:
                        continue

                    # only increase the index if the word exists
                    words[word], index = index, index + 1

        return words

    def _get_tf_vec(self, line):
        tf_vec = get_empty_vec(len(self._words))

        for word in self._get_clean_words(line):
            tf_vec[self._get_word_index(word)] += 1

        return tf_vec

    def _get_idf_vector(self, filepath):
        idf_vec = get_empty_vec(len(self._words))
        words_of_file = []

        with open(filepath, 'r') as f:
            for lineno, raw_line in enumerate(f):
                line = raw_line[:raw_line.index("\t")]
                words_of_file.extend(set(self._get_clean_words(line)))

        for word, df in Counter(words_of_file).iteritems():
            idf_vec[self._get_word_index(word)] = math.log(lineno / df)

        return idf_vec

    def _tf_to_wf(self, tf):
        tf_len = len(tf)
        wf = get_empty_vec(tf_len)

        for i in range(tf_len):
            tf_val = tf[i]
            if tf_val == 0:
                continue

            wf[i] = 1 + math.log(tf_val)

        return wf

    def build_set(self, *args, **kwargs):
        """
        build a set of a given type
        """
        if self._vector_type == BOOLEAN:
            return self._build_set_boolean(*args, **kwargs)

        if self._vector_type == TF:
            return self._build_set_tf(*args)

        if self._vector_type == TFIDF:
            return self._build_set_tfidf(*args)

    def _build_set_boolean(self, filepath):
        doc_set = {}

        with open(filepath, 'r') as f:
            for index, line in enumerate(f):
                vec = get_empty_vec(len(self._words))

                raw_line, raw_doc_class = line.split("\t")
                for word in self._get_clean_words(raw_line):
                    vec[self._get_word_index(word)] = 1

                vec.append(raw_doc_class.rstrip())
                doc_set['doc' + str(index)] = vec

        return doc_set

    def _build_set_tf(self, filepath):
        doc_set = {}

        with open(filepath, 'r') as f:
            for index, line in enumerate(f):
                raw_line, raw_doc_class = line.split("\t")
                tf_vec = self._get_tf_vec(raw_line)

                wf_vec = self._tf_to_wf(tf_vec) \
                    + [raw_doc_class.rstrip()]

                doc_set['doc' + str(index)] = wf_vec

        return doc_set

    def _build_set_tfidf(self, filepath):
        doc_set, idf_vec = {}, self._get_idf_vector(filepath)

        with open(filepath, 'r') as f:

            for index, line in enumerate(f):
                tfidf_vec = get_empty_vec(len(self._words))
                raw_line, raw_doc_class = line.split("\t")
                tf_vec = self._get_tf_vec(raw_line)

                for i in range(len(tf_vec)):
                    tfidf_vec[i] = idf_vec[i] * tf_vec[i]

                tfidf_vec.append(raw_doc_class.rstrip())
                doc_set['doc' + str(index)] = tfidf_vec

        return doc_set

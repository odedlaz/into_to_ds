import re

BOOLEAN_TYPE = 'boolean'
TF_TYPE = 'tf'
TFIDF_TYPE = 'tfidf'


punctuation_marks = [".", "?", "!",
                     ";", ":", "-",
                     "[", "]",
                     "(", ")",
                     "{", "}",
                     "'", '"', "*"]

puncs_pattern = "[%s]" % re.escape("".join(punctuation_marks))


class FileReader:
    def __init__(self, input_file, words_filter=[], vector_type=BOOLEAN_TYPE):

        if vector_type not in (BOOLEAN_TYPE, TF_TYPE, TFIDF_TYPE):
            raise ValueError("vector type is not supported")

        self.file = input_file
        self._vector_type = vector_type
        self.df = {}  # type: Dict[str, int]

        self._words_filter = set(map(str.lower, words_filter))
        self._puncs_re = re.compile(puncs_pattern, re.IGNORECASE)

        self.words = self.create_words_bank()

    def _get_clean_words(self, line):
        # remove punctuation marks from line
        stripped_line = self._puncs_re.sub("", line.strip())

        # yield words that shouldn't be filtered
        for word in map(str.lower, stripped_line.split(" ")):
            if word in self._words_filter:
                continue

            yield word

    def build_set(self, *args, **kwargs):
        if self._vector_type == BOOLEAN_TYPE:
            return self._build_set_boolean(*args, **kwargs)

        if self._vector_type == TF_TYPE:
            return self._build_set_tf(*args, **kwargs)

        if self._vector_type == TFIDF_TYPE:
            return self._build_set_tfidf(*args, **kwargs)

    def create_words_bank(self):
        # starting with 1 because 0 cant serve as a dictionary key
        index = 1

        words = {}
        with open(self.file, 'r') as f:
            for raw_line in f:
                line = raw_line[:raw_line.index("\t")]
                for word in self._get_clean_words(line):
                    # if the word already exists -> discard it
                    if word in words:
                        continue

                    # only increase the index if the word exists
                    # TODO: understand why?!
                    words[word], index = index, index + 1

        return words

    def _build_set_boolean(self, file_to_vector):
        doc_set = {}

        with open(file_to_vector, 'r') as f:
            for index, line in enumerate(f):
                vec = len(self.words) * [0]

                raw_line, raw_doc_class = line.split("\t")
                for word in self._get_clean_words(raw_line):
                    vec[self.words[word] - 1] = 1

                vec.append(raw_doc_class.rstrip())
                doc_set['doc' + str(index)] = vec

        return doc_set

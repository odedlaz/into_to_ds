import os
import sys

# make stdout to get ignored
sys.stdout = open(os.devnull, 'w')

import tempfile
from uuid import uuid4

from nltk import corpus

from review import Reviewer

test_corpus = {
    "neg": {
        "14_3.txt": "Mary like movies too"
    },
    "pos": {
        "10_7.txt": "John likes to watch movies. Mary likes movies too"
    }
}

stopwords = corpus.stopwords.words('english')

raw_output = '''3 qid:14 mari:1 like:1 movi:1 # 14_3.txt
7 qid:10 john:1 like:2 watch:1 movi:2 mari:1 # 10_7.txt'''

raw_tfidf_output = '''3 qid:14 mari:0.0 like:0.0 movi:0.0 # 14_3.txt
7 qid:10 john:0.693 like:0.0 watch:0.693 movi:0.0 mari:0.0 # 10_7.txt'''


svmlight_output = '''3 qid:14 2:1 3:1 4:1 # 14_3.txt
7 qid:10 1:1 2:2 3:1 4:2 5:1 # 10_7.txt'''

svmlight_tfidf_output = '''3 qid:14 2:0.0 3:0.0 4:0.0 # 14_3.txt
7 qid:10 1:0.693 2:0.0 3:0.0 4:0.0 5:0.693 # 10_7.txt'''


def test_raw_no_tfidf():
    dirs = list(write_corpus())
    reviewer = Reviewer(words_filter=stopwords,
                        output_per_dir=False,
                        output_in_svm_light=False,
                        output_in_tfidf=False,
                        *dirs)

    reviewer.write()

    with open("dataset_slt.txt", "r") as f:
        assert f.read().strip() == raw_output


def test_raw_with_tfidf():
    dirs = list(write_corpus())
    reviewer = Reviewer(words_filter=stopwords,
                        output_per_dir=False,
                        output_in_svm_light=False,
                        output_in_tfidf=True,
                        *dirs)

    reviewer.write()

    with open("dataset_slT.txt", "r") as f:
        assert f.read().strip() == raw_tfidf_output


def test_svmlight_no_tfidf():
    dirs = list(write_corpus())
    reviewer = Reviewer(words_filter=stopwords,
                        output_per_dir=False,
                        output_in_svm_light=True,
                        output_in_tfidf=False,
                        *dirs)

    reviewer.write()

    with open("dataset_sLt.txt", "r") as f:
        assert f.read().strip() == svmlight_output


def test_svmlight_with_tfidf():
    dirs = list(write_corpus())
    reviewer = Reviewer(words_filter=stopwords,
                        output_per_dir=False,
                        output_in_svm_light=True,
                        output_in_tfidf=True,
                        *dirs)

    reviewer.write()

    with open("dataset_sLT.txt", "r") as f:
        assert f.read().strip() == svmlight_tfidf_output


def write_corpus():
    tempdir = os.path.join(tempfile.gettempdir(),
                           str(uuid4()).replace("-", ""))
    os.makedirs(tempdir)

    for pardir, files in test_corpus.items():
        pardirpath = os.path.join(tempdir, pardir)
        os.makedirs(pardirpath)
        for filename, content in files.items():
            with open(os.path.join(pardirpath, filename), 'w') as f:
                f.write(content)

        yield pardirpath


if __name__ == "__main__":

    test_raw_no_tfidf()
    test_raw_with_tfidf()
    test_svmlight_no_tfidf()
    test_svmlight_with_tfidf()

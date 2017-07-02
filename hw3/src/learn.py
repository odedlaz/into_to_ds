import warnings
warnings.warn = lambda *a, **kw: None

import argparse
import sys
from collections import namedtuple

from sklearn import datasets, metrics, preprocessing, svm

import utils

SvmSet = namedtuple('SvmSet', ['x', 'y', 'qid'])


def parse_arguments(args=None):
    parser = argparse.ArgumentParser(description='Bag of Words')

    parser.add_argument('train',
                        action=utils.argparse.ValidateFilepath,
                        help='path to the train set in svm light format')

    parser.add_argument('test',
                        action=utils.argparse.ValidateFilepath,
                        help='path to the test set in svm light format')

    return parser.parse_args(args or sys.argv[1:])


def load_dataset(train_path, test_path, threshold=5):
    files = [train_path, test_path]
    dataset = datasets.load_svmlight_files(files=files,
                                           zero_based=True,
                                           query_id=True,
                                           multilabel=False)
    for (x, y, qid) in [dataset[i:i + 3]
                        for i in range(0, len(dataset), 3)]:
        x.data = preprocessing.MinMaxScaler().fit_transform(x.data)

        for idx, score in enumerate(y):
            y[idx] = 1 if score > threshold else 0

        yield SvmSet(x=x, y=y, qid=qid)


def train_svm(train_set):
    classifier = svm.LinearSVC()
    classifier.fit(train_set.x, train_set.y)
    return classifier


def test_svm(classifier, test_set):
    predicted = classifier.predict(test_set.x)
    predict_fmt = "{filename}:{prediction:.0f}\n"

    with open('learn.txt', 'w') as f:
        for filename, prediction in zip(filename_generator(test_set), predicted):
            f.write(predict_fmt.format(**locals()))

    report = metrics.classification_report(test_set.y, predicted)
    score = classifier.score(test_set.x, test_set.y)

    msg_format = ("The score is: {}\n\n"
                  "The classification matrix is: \n{}")

    print(msg_format.format(score, report))


def filename_generator(test_set):
    fmt = "{qid}_{y}.txt"
    for y, qid in zip(test_set.y, test_set.qid):
        yield fmt.format(**locals())


def print_weights(classifier):
    sorted_weights = sorted(classifier.coef_[0])

    for name, weights in {"highest": sorted_weights[-10:],
                          "lowest": sorted_weights[:10]}.items():

        print("\n{} weights:\n".format(name).title())
        for weight in weights:
            print("{}- {}".format(" " * 3, weight))


def run_svm(train_path, test_path):
    train_set, test_set = tuple(load_dataset(train_path, test_path))
    classifier = train_svm(train_set)
    test_svm(classifier, test_set)
    print_weights(classifier)


def main(*args):
    argument_parser = parse_arguments(args)
    run_svm(argument_parser.train,
            argument_parser.test)


if __name__ == "__main__":
    main(*sys.argv[1:])

import argparse
import sys
from collections import namedtuple

from sklearn import datasets, metrics, preprocessing, svm

import utils

SvmSet = namedtuple('SvmSet', ['x', 'y'])


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
                                           zero_based=False,
                                           multilabel=False)

    for (x, y) in zip(dataset[::2], dataset[1::2]):
        x.data = preprocessing.MinMaxScaler().fit_transform(x.data)

        for idx, score in enumerate(y):
            y[idx] = 1 if score > threshold else 0

        yield SvmSet(x=x, y=y)


def train_svm(train_set):
    classifier = svm.LinearSVC()
    classifier.fit(train_set.x, train_set.y)
    return classifier


def test_svm(classifier, test_set):
    predicted = classifier.predict(test_set.x)
    report = metrics.classification_report(test_set.y, predicted)
    print(report)


def run_svm(train_path, test_path):
    train_set, test_set = tuple(load_dataset(train_path, test_path))

    classifier = train_svm(train_set)
    test_svm(classifier, test_set)


def main(*args):
    argument_parser = parse_arguments(args)
    run_svm(argument_parser.train,
            argument_parser.test)


if __name__ == "__main__":
    main(*sys.argv[1:])

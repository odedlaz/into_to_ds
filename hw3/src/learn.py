from sklearn import datasets

from sklearn import svm

from sklearn import preprocessing

import sys


def learn_svm(train_set_file, test_set_file): # train set has 50166 ,test set has 70564
    train_set = datasets.load_svmlight_file(train_set_file, zero_based=True, multilabel=True, n_features=70564)

    test_set = datasets.load_svmlight_file(test_set_file, zero_based=True, multilabel=True, n_features=70564)

    train_x = train_set[0]

    train_x.data = preprocessing.MinMaxScaler().fit_transform(train_x.data)

    train_y = train_set[1]

    test_x = test_set[0]

    test_x.data = preprocessing.MinMaxScaler().fit_transform(test_x.data)

    test_y = test_set[1]

    classifier = svm.SVC()

    classifier.fit(train_x, train_y)

    predicted = classifier.predict(test_x)

    print(predicted)

    print(test_y)

    # from sklearn.model_selection import cross_val_score

    # scores = cross_val_score(classifier, test_x, test_y)

    # print(scores)


if __name__ == "__main__":
    train_path = sys.argv[1]

    test_path = sys.argv[2]

    learn_svm(train_path, test_path)

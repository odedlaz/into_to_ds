from sklearn import datasets

from sklearn import svm

from sklearn import preprocessing

import sys

def score_normalizer(scores,threshold):
    for index, score in enumerate(scores):
        scores[index] = 1 if score>threshold else 0
    return scores


def learn_svm(train_set_file, test_set_file): # train set has 50166 ,test set has 70564
    train_set = datasets.load_svmlight_file(train_set_file, zero_based=True, multilabel=False, n_features=70568)

    test_set = datasets.load_svmlight_file(test_set_file, zero_based=True, multilabel=False, n_features=70568)

    train_x = train_set[0]

    train_x.data = preprocessing.MinMaxScaler().fit_transform(train_x.data)

    threshold = 5

    train_y = score_normalizer(train_set[1], threshold)

    test_x = test_set[0]

    test_x.data = preprocessing.MinMaxScaler().fit_transform(test_x.data)

    test_y = score_normalizer(test_set[1], threshold)

    classifier = svm.LinearSVC()

    classifier.fit(train_x, train_y)

    predicted = classifier.predict(test_x)

    print(predicted)

    print(test_y)

    from sklearn.model_selection import cross_val_score

    scores = cross_val_score(classifier, test_x, test_y)

    print(scores)


if __name__ == "__main__":
    train_path = sys.argv[1]

    test_path = sys.argv[2]

    learn_svm(train_path, test_path)

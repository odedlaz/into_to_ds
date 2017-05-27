import math


def training(training_set):
    class_centroids = {}
    for doc in training_set:
        doc_class = training_set[doc][-1]
        if doc_class not in class_centroids.keys():
            class_centroids[doc_class] = training_set[doc][0:-1]
        else:
            class_centroids[doc_class] = [class_centroids[doc_class][i] + training_set[doc][0:-1][i] for i in range(len(training_set[doc]) - 1)]
    for c in class_centroids.keys():
        class_size = len(class_centroids[c])
        for i in range(class_size):
            class_centroids[c][i] /= float(class_size)
    return class_centroids


def predict(class_centroids, doc_vec):
    return None


def euclidean_dist(vec1, vec2):
    return math.sqrt(map(lambda x: math.pow(x[0] - x[1], 2), zip(vec1, vec2)))

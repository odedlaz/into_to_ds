import math
from itertools import starmap


def training(training_set):
    class_centroids = {}
    for doc in training_set:
        doc_class = training_set[doc][-1]
        if doc_class not in class_centroids.keys():
            class_centroids[doc_class] = training_set[doc][0:-1]
        else:
            class_centroids[doc_class] = [class_centroids[doc_class][i] + training_set[doc][0:-1][i] for i in
                                          range(len(training_set[doc]) - 1)]
    for c in class_centroids.keys():
        class_size = len(class_centroids[c])
        for i in range(class_size):
            class_centroids[c][i] /= float(class_size)

    return class_centroids


#
# predicts a doc_vec sentiment using proximity to centroids
#
def predict(class_centroids, doc_vec):
    items = class_centroids.iteritems()
    min_cluster, item_vec = next(items)
    min_dist = euclidean_dist(item_vec, doc_vec)

    for item_class, item_vec in items:
        dist = euclidean_dist(item_vec, doc_vec)

        if (dist < min_dist):
            min_dist = dist
            min_cluster = item_class

    return min_cluster

# calculates eculidean distance between vec1 and vec2
# creates a list of (x-y)^2 where as x and y is values of vec1 & vec2 accordingly.
# returns the square root of sum of the above list.

def euclidean_dist(vec1, vec2):
    return math.sqrt(sum(starmap(lambda x, y: math.pow(x - y, 2), zip(vec1, vec2))))

import itertools
import math


def euclidean_dist(vec1, vec2):
    return math.sqrt(sum(itertools.starmap(lambda x, y: math.pow(x - y, 2),
                                           zip(vec1, vec2))))


def magnitude(vec):
    return math.sqrt(sum(x**2 for x in vec))


def sin_similarity(vec1, vec2):
    dot_product = sum(itertools.starmap(lambda x, y: x * y,
                                        zip(vec1, vec2)))
    return dot_product / (magnitude(vec1) * magnitude(vec2))

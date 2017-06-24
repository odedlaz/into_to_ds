from itertools import starmap
import math


class EuclideanDistance(object):
    @staticmethod
    def calculate(vec1, vec2):
        return math.sqrt(sum(starmap(lambda x, y: math.pow(x - y, 2),
                                     zip(vec1, vec2))))

    @staticmethod
    def compare(score_x, score_y):
        return score_x < score_y


class CosineDistance(object):

    @staticmethod
    def magnitude(vec):
        return math.sqrt(sum(x**2 for x in vec))

    @staticmethod
    def calculate(vec1, vec2):
        dot_product = sum(starmap(lambda x, y: x * y,
                                  zip(vec1, vec2)))

        vec1m = CosineDistance.magnitude(vec1)
        vec2m = CosineDistance.magnitude(vec2)

        return dot_product / (vec1m * vec2m)

    @staticmethod
    def compare(score_x, score_y):
        return score_x > score_y

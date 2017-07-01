import os
from collections import OrderedDict


class Review(object):
    review_fmt = "{score} {bag_txt} # {filename}"

    SVM = "svm"
    RAW = "raw"

    def __init__(self, path, words, score):
        self.path = path
        self.filename = os.path.basename(self.path)
        self.words = words
        self.score = score

    def __iter__(self):
        return self.words.__iter__()

    def format(self, bag_of_words, format=RAW):
        if format == Review.SVM:
            return self._format_in_svm_light(bag_of_words)

        if format == Review.RAW:
            return self._format_in_raw(bag_of_words)

        raise ValueError("format is not supported")

    def _format(self, words):
        bag_txt = " ".join("{}:{}".format(w, sum)
                           for w, sum in words.items())

        return self.review_fmt.format(score=self.score,
                                      bag_txt=bag_txt,
                                      filename=self.filename)

    def _format_in_raw(self, bag_of_words):
        return self._format(self.words)

    def _format_in_svm_light(self, bag_of_words):
        svm_data = OrderedDict(((bag_of_words[w], sum) for w, sum
                                in sorted(self.words.items(),
                                          key=lambda x: x[0])))
        return self._format(svm_data)

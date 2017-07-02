import sys


class ProgressBar(object):

    def __init__(self, prefix, numofitems, file=sys.stdout):
        self._numofitems = numofitems
        self._counter = 0
        self._file = file
        self._report_fmt = prefix + "... {0:.1f}%"

    def report(self):
        self._counter += 1
        progress = self._counter * 100.0 / self._numofitems

        line = self._report_fmt.format(progress)
        print(line, end='', file=self._file)
        print('\r' * len(line), end='', file=self._file)

    def __enter__(self):
        return self

    def __exit__(self, type, value, tb):
        print("", file=self._file)

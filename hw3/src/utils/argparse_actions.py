import argparse
import os
import codecs
import nltk


class ValidateDirectoriesAction(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):

        error_fmt = "'{}' dir doesn't exist"
        for dir in values:
            if not os.path.isdir(dir):
                raise argparse.ArgumentError(self, error_fmt.format(dir))

        setattr(namespace, self.dest, values)


class ValidateFilepath(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):

        if not os.path.exists(values):
            msg = "'{}' doesn't exist".format(values)
            raise argparse.ArgumentError(self, msg)

        if not os.path.isfile(values):
            msg = "'{}' is not a file".format(values)
            raise argparse.ArgumentError(self, msg)

        setattr(namespace, self.dest, values)


class LoadStopWordsAction(argparse.Action):

    def _get_stopwords(self, path):
        # we've added the possibility to add a custom words bank
        # if the file doesn't exist, we fallback to ntlk's corpus
        if os.path.isfile(path):
            with codecs.open(path, "r", encoding='utf-8') as f:
                return [x.strip() for x in f]

        try:
            return nltk.corpus.stopwords.words('english')
        except LookupError:
            msg = 'stopwords file is missing, and nltk corpus is not installed'
            raise argparse.ArgumentError(self, msg)

    def __call__(self, parser, namespace, values, option_string=None):
        setattr(namespace,
                self.dest,
                self._get_stopwords(values))

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


class LoadStopWordsAction(argparse.Action):

    def _get_stopwords(self, path):
        # we've taken lab9's stop words file, and combined it with nltk's
        # how? we wrote nltk's to disk, added to lab9's, and cleaned duplicates.
        # if the file doesn't exist for some reason, fallback to ntlk's corpus
        if os.path.isfile(path):
            with codecs.open(path, "r", encoding='utf-8') as f:
                return [x.strip() for x in f]

        try:
            return nltk.corpus.stopwords.words('english')
        except LookupError:
            msg = 'stopwords file is missing, and nltk corpus is not installed'
            raise argparse.ArgumentTypeError(msg)

    def __call__(self, parser, namespace, values, option_string=None):
        setattr(namespace,
                self.dest,
                self._get_stopwords(values))

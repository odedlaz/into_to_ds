from shutil import copyfile

import dataset
import file_reader
from consts import BOOLEAN, BOOLEAN_TYPE, TFIDF, TFIDF_TYPE
from similarity import CosineDistance

eval_types = {
    BOOLEAN_TYPE: BOOLEAN,
    TFIDF_TYPE: TFIDF
}


class AdhocEval(object):
    def __init__(self, k, query, method):

        if method not in eval_types:
            raise ValueError("method is not supported")

        self.k = k
        self.query_method = eval_types[method]
        self.combine_file = self.build_combine_file(query)

        with open(self.combine_file) as f:
            self.combine_file_last_line = sum(1 for _ in f) - 1

        full_fr = file_reader.FileReader(self.combine_file,
                                         words_filter=dataset.stop_words,
                                         vector_type=TFIDF)

        combine_tfidf_set = full_fr.build_set(self.combine_file)

        del combine_tfidf_set['doc' + str(self.combine_file_last_line)]

        self.full_set = combine_tfidf_set

        self.query_vec = self.build_query_vec()

    def build_combine_file(self, query):
        combine_file = 'combine_set.txt'
        copyfile(dataset.FULL_FILE, combine_file)
        with open(combine_file, 'a') as f:
            f.write(query + "\t1")
        return combine_file

    def build_query_vec(self):

        query_fr = file_reader.FileReader(self.combine_file,
                                          words_filter=dataset.stop_words,
                                          vector_type=self.query_method)
        query_set = query_fr.build_set(self.combine_file)

        # the vector of query
        return query_set['doc' + str(self.combine_file_last_line)][0:-1]

    def calc_k_docs(self):
        k_docs = []  # list of tuples (doc#, cosine)
        index = 0
        for doc in self.full_set:
            curr_cosine = CosineDistance.calculate(self.full_set[doc][0:-1],
                                                   self.query_vec)

            if index < self.k:  # puts k first values
                k_docs.append((doc, curr_cosine))
                index += 1
                continue
            # sorts tuples by second value(increasing order)
            k_docs.sort(key=lambda x: x[1])
            if curr_cosine > k_docs[0][1]:  # worst similarity in list
                k_docs[0] = (doc, curr_cosine)

        k_docs.sort(key=lambda x: x[1], reverse=True)

        return k_docs

    def print_results(self):
        k_docs = self.calc_k_docs()
        for doc in k_docs:
            doc_num = int(doc[0][3:])
            with open(dataset.FULL_FILE, 'r') as f:
                for index, raw_line in enumerate(f):
                    if index == doc_num:
                        doc_text = raw_line[:raw_line.index("\t")]
                        break

            print doc[0], "-", doc_text, "Score:", doc[1]

import math
# from typing import Dict

class File_Reader:
    def __init__(self, input_file, vector_type='boolean'):
        self.file = input_file
        self.vector_type = vector_type
        self.words = {}  # type: Dict[str, int]
        self.df = {}  # type: Dict[str, int]
        self.create_words_bank()
        if self.vector_type == 'boolean':
            self.build_set = self.build_set_boolean
        if self.vector_type == 'tf':
            self.build_set = self.build_set_tf
        if self.vector_type == 'tfidf':
            self.build_set = self.build_set_tfidf

    @property
    def vector_type(self):
        return self.vector_type

    @vector_type.setter
    def vector_type(self, value):
        if value in ('boolean', 'tf', 'tfidf'):
            self.vector_type = value

    def create_words_bank(self):
        index = 1 # starting with 1 because 0 cant serve as a dictionary key
        with open(self.file, 'r') as reader: # open the file "file"
            for line in reader: # for each line in file
                for word in line.split("\t")[0].split(): # for each word in the line
                    if word not in self.words.keys(): # if the word doesnt already exists in the words dictionary
                        self.words[word] = index # add it
                        index += 1

    def build_set_boolean(self, file_to_vector):
        doc_set = {}
        index = 0
        with open(file_to_vector, 'r') as reader:
            for line in reader:
                vec = len(self.words)*[0,]
                for word in line.split("\t")[0].split():
                    vec[self.words[word]-1] = 1
                doc_class = line.split("\t")[1].rstrip()
                vec.append(doc_class)
                doc_set['doc'+str(index)] = vec
                index += 1
        return doc_set


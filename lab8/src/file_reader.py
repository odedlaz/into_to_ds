
def create_words_bank(file):
    words = {} # create a new dictionary - mapping a word to its index in the vector representation
    index = 1 # starting with 1 because 0 cant serve as a dictionary key
    with open(file, 'r') as reader: # open the file "file"
        for line in reader: # for each line in file
            for word in line.split("\t")[0].split(): # for each word in the line
                if word not in words.keys(): # if the word doesnt already exists in the words dictionary
                    words[word] = index # add it
                    index += 1
    return words


def build_set(file, words):
    doc_set = {}
    index = 0
    with open(file, 'r') as reader:
        for line in reader:
            vec = len(words)*[0,]
            for word in line.split("\t")[0].split():
                vec[words[word]-1] = 1
            doc_class = line.split("\t")[1].rstrip()
            vec.append(doc_class)
            doc_set['doc'+str(index)] = vec
            index += 1
    return doc_set

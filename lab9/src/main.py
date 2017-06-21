import file_reader
import rocchio_classifier
import similarity


def get_stop_words():
    with open("../dataset/stop_words.txt", "r") as f:
        return [x.strip() for x in f.readlines()]


def svm_light_format(full_set):
    with open("./svm_light_format.txt", 'w') as output:
        for key in full_set:
            index = 1
            output.write(full_set[key][-1] + ' ')
            for feature in range(len(full_set[key]) - 1):
                if full_set[key][feature] != 0:
                    output.write(str(index) + ':' +
                                 str(full_set[key][feature]) + ' ')
                index += 1
            output.write('#' + key + '\n')


def calc_accuracy(test_set, classifier):
    correct = 0.0
    total = len(test_set.keys())
    for key in test_set:
        real = test_set[key][-1]
        predicted = classifier.predict(test_set[key][0: -1], similarity.euclidean_dist)
        print(real, predicted)
        if real == predicted:
            correct += 1.0
    return correct / total


TEST_DATASET = "../dataset/amazon_cells_labelled_test.txt"
FULL_DATASET = "../dataset/amazon_cells_labelled_full.txt"
TRAIN_DATASET = "../dataset/amazon_cells_labelled_train.txt"

if __name__ == '__main__':
    file_reader = file_reader.FileReader(FULL_DATASET,
                                         words_filter=get_stop_words(),
                                         vector_type='boolean')
    full_set = file_reader.build_set(FULL_DATASET)
    train_set = file_reader.build_set(TRAIN_DATASET)
    test_set = file_reader.build_set(TEST_DATASET)
    classifier = rocchio_classifier.Rocchio_Classifier(train_set)
    print(calc_accuracy(test_set, classifier))
    svm_light_format(full_set)

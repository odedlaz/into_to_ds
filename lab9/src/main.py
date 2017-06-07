import file_reader
import rocchio_classifier


def svm_light_format(full_set):
    with open("./svm_light_format.txt", 'w') as output:
        for key in full_set:
            index = 1
            output.write(full_set[key][-1] + ' ')
            for feature in range(len(full_set[key])-1):
                if full_set[key][feature] != 0:
                    output.write(str(index) + ':' + str(full_set[key][feature]) + ' ')
                index += 1
            output.write('#' + key + '\n')


def calc_accuracy(test_set, classifier):
    correct = 0.0
    total = len(test_set.keys())
    for key in test_set:
        real = test_set[key][-1]
        predicted = classifier.predict(test_set[key][0:-1])
        print(real, predicted)
        if real == predicted:
            correct += 1.0
    return correct/total


if __name__ == '__main__':
    file_name = "./dataset/amazon_cells_labelled_full.txt"
    file_reader = file_reader.File_Reader(file_name, 'boolean')
    file_reader.vector_type = 'boolean'
    full_set = file_reader.build_set(file_name)
    train_set = file_reader.build_set("./dataset/amazon_cells_labelled_train.txt")
    test_set = file_reader.build_set("./dataset/amazon_cells_labelled_test.txt")
    classifier = rocchio_classifier.Rocchio_Classifier(train_set)
    print(calc_accuracy(test_set, classifier))
    svm_light_format(full_set)




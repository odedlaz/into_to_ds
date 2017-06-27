import file_reader
import rocchio_classifier
import similarity
import dataset


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
        predicted = classifier.predict(test_set[key][0: -1],
                                       similarity.CosineDistance)
        print(real, predicted)
        if real == predicted:
            correct += 1.0
    return correct / total


if __name__ == '__main__':
    file_reader = file_reader.FileReader(dataset.FULL_FILE,
                                         words_filter=dataset.stop_words,
                                         vector_type='tfidf')

    full_set = file_reader.build_set(dataset.FULL_FILE)
    train_set = file_reader.build_set(dataset.TRAIN_FILE)
    test_set = file_reader.build_set(dataset.TEST_FILE)

    classifier = rocchio_classifier.Rocchio_Classifier(train_set)
    print(calc_accuracy(test_set, classifier))
    # # svm_light_format(full_set)
    # k, queryID, query, rep_method = int(sys.argv[1]), sys.argv[2],str(sys.argv[3]), int(sys.argv[4])
    # eval = AdhocEval(k, query, rep_method)
    # output_file = "Output_"+str(queryID)+"_"+str(rep_method)+".txt"
    # output_dir = open(output_file, 'w')
    # sys.stdout = output_dir
    # eval.print_results()
    # sys.stdout = sys.__stdout__
    # output_dir.close()

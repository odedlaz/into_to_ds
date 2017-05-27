import file_reader
import rocchio_classifier

def calc_accuracy(test_set, class_centroids):
    correct = 0.0
    total = len(test_set.keys())
    for key in test_set:
        real = test_set[key][-1]
        predicted = rocchio_classifier.predict(class_centroids, test_set[key][0:-1])
        print(real, predicted)
        if real == predicted:
            correct += 1.0
    return (correct/total)


if __name__ == '__main__':
    file_name = "./dataset/amazon_cells_labelled_full.txt"
    word_bank = file_reader.create_words_bank(file_name)
    full_set = file_reader.build_set(file_name, word_bank)
    train_set = file_reader.build_set("./dataset/amazon_cells_labelled_train.txt", word_bank)
    test_set = file_reader.build_set("./dataset/amazon_cells_labelled_test.txt", word_bank)
    class_centroids = rocchio_classifier.training(train_set)
    print(calc_accuracy(test_set, class_centroids))

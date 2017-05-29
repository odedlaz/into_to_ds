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
    return (correct / total)


def get_svm_light_lines(aset):
    for doc, vec in aset.iteritems():
        vec, target = vec[:-1], vec[-1]

        # we can remove the exists == 1 statement
        # to return all the features, not only the existing ones
        features = ((lineno + 1, exists)
                    for (lineno, exists) in enumerate(vec)
                    if exists == 1)

        # get the feature text, sorted by line number
        feature_text = " ".join("{}:{}".format(lineno, exists)
                                for lineno, exists in sorted(features,
                                                             key=lambda x: x[0]))

        yield " ".join([target, feature_text, "#" + doc])


def write_in_svm_light(aset, targetfile):
    with open(targetfile, 'w') as f:
        f.writelines(l + '\n' for l in get_svm_light_lines(aset))


if __name__ == "__main__":
    file_name = "../dataset/amazon_cells_labelled_full.txt"
    word_bank = file_reader.create_words_bank(file_name)
    full_set = file_reader.build_set(file_name, word_bank)
    train_set = file_reader.build_set("../dataset/amazon_cells_labelled_train.txt", word_bank)
    test_set = file_reader.build_set("../dataset/amazon_cells_labelled_test.txt", word_bank)

    write_in_svm_light(test_set, 'test_svm')
    write_in_svm_light(full_set, 'full_svm')

    class_centroids = rocchio_classifier.training(train_set)
    print(calc_accuracy(test_set, class_centroids))

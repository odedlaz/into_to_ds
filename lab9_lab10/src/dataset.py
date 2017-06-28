TEST_FILE = "../dataset/amazon_cells_labelled_test.txt"
FULL_FILE = "../dataset/amazon_cells_labelled_full.txt"
TRAIN_FILE = "../dataset/amazon_cells_labelled_train.txt"
STOP_WORDS_FILE = "../dataset/stop_words.txt"


with open(STOP_WORDS_FILE, "r") as f:
    stop_words = [x.strip() for x in f.readlines()]

class Rocchio_Classifier:
    def __init__(self, train_set):
        self.training_set = train_set
        self.class_centroids = {}
        self.training()

    def training(self):
        for doc in self.training_set:
            doc_class = self.training_set[doc][-1]
            if doc_class not in self.class_centroids:
                self.class_centroids[doc_class] = self.training_set[doc][0:-1]
                continue

            self.class_centroids[doc_class] = [self.class_centroids[doc_class][i] + self.training_set[doc][0:-1][i]
                                               for i in range(len(self.training_set[doc]) - 1)]

        for centroid in self.class_centroids:
            class_size = len(self.class_centroids[centroid])
            for i in range(class_size):
                self.class_centroids[centroid][i] /= float(class_size)

        print self.class_centroids.keys()

    def predict(self, doc_vec, similarity):
        centroids = self.class_centroids.iteritems()
        min_cluster, centroid_vec = next(centroids)
        min_score = similarity.calculate(centroid_vec, doc_vec)

        for item_class, centroid_vec in centroids:
            score = similarity(centroid_vec, doc_vec)
            if similarity.compare(score, min_score):
                min_score = score
                min_cluster = item_class

        return min_cluster

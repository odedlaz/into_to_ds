#include <iostream>
#include "include/ClusterReader.h"
#include "include/SilhouetteCoeff.h"
#include "include/WSS.h"
#include "include/BSS.h"
#include "include/TSS.h"
#include "include/Purity.h"


using std::string;
using std::vector;
using std::endl;

void printSilhouetteCoeff(const vector<Cluster> &clusters, size_t dimension) {
    SilhouetteCoeff coeff(clusters, dimension);
    std::cout << "Silhouette total: " << coeff.calculate() << endl;
    for (std::vector<Cluster>::size_type i = 0; i != clusters.size(); i++) {
        std::cout << "Silhouette Cluster " << i << " : " << coeff.calculate(clusters[i]) << endl;
    }
    size_t clusterID = 2;
    for (size_t j = 0; j < clusters[clusterID].getSize(); j++) {
        clusters[clusterID][j].print();
        std::cout << "Silhouette point " << coeff.calculate(clusters[clusterID][j]) << endl;
    }
}

void printWSS(const vector<Cluster> &clusters, size_t dimension) {
    WSS wss(clusters, dimension);
    std::cout << "WSS: " << wss.calculate() << endl;
    for (std::vector<Cluster>::size_type i = 0; i != clusters.size(); i++) {
        std::cout << "Cluster " << i << " : " << wss.calculate(clusters[i]) << endl;
    }
}

void printBSS(const vector<Cluster> &clusters, size_t dimension) {
    BSS bss(clusters, dimension);
    std::cout << "BSS: " << bss.calculate() << endl;
}


void printTSS(const vector<Cluster> &clusters, size_t dimension) {
    TSS tss(clusters, dimension );
    std::cout << "TSS: " << tss.calculate() << endl;
}

void printPurity(const vector<Cluster> &clusters, size_t dimension) {
    Purity purity(clusters, dimension);
    std::cout << "Purity: " << purity.calculate() << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Missing data file" << std::endl;
        return 1;
    }
    ClusterReader reader(argv[1]);
    if (!reader.loadClusters()) return 1;
    printSilhouetteCoeff(reader.getClusters(), reader.getPointsDimension());
    printWSS(reader.getClusters(), reader.getPointsDimension());
    printBSS(reader.getClusters(), reader.getPointsDimension());
    printTSS(reader.getClusters(), reader.getPointsDimension() );
    printPurity(reader.getClusters(), reader.getPointsDimension());
    return 0;
}
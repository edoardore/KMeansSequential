#include <iostream>
#include <chrono>
#include <omp.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <windef.h>
#include "Cluster.h"


double Range = 100000;
const int nPoint = 5000;
int nCluster = 5;
int itr = 20;

using namespace std;
using namespace std::chrono;

void initPoint(struct point *points, int numPoint);

void initPointArray(struct pointArray *points, int numPoint);

vector<Cluster> initCluster(int numCluster);

void computeDistancePoint(struct point *points, vector<Cluster> &clusters, int nPoint);

void computeDistancePointArray(struct pointArray *points, vector<Cluster> &clusters, int nPoint);

double euclideanDistPoint(struct point p, Cluster c);

double euclideanDistPointArray(double x, double y, Cluster c);

bool updateClusters(vector<Cluster> &clusters);

void drawChartPoint(struct point *points, int nPoint);

void drawChartPointArray(struct pointArray *points, int nPoint);

struct point {
    double x;
    double y;
    int clusterID;
};

struct pointArray {
    double x[nPoint];
    double y[nPoint];
    int clusterID[nPoint];
};

int main() {
    bool AoS = TRUE;
    bool SoA = TRUE;
    if (AoS) {
        cout << "**********************Points in AoS************************\n";
        srand(time(NULL));
        double timeStart = omp_get_wtime();
        cout << "Creazione di " << nPoint << " punti casuali\n";
        struct point points[nPoint];
        initPoint(points, nPoint);
        cout << "Creazione di " << nCluster << " Clusters\n";
        vector<Cluster> clusters = initCluster(nCluster);
        double end = omp_get_wtime();
        auto duration = end - timeStart;
        cout << "Punti e Clusters generati in: " << duration << "s\n";
        bool updated = true;
        int iterations = 0;
        while (updated && iterations < itr) {
            iterations++;
            computeDistancePoint(points, clusters, nPoint);
            updated = updateClusters(clusters);
        }
        double time = omp_get_wtime();
        duration = time - end;
        cout << "Aggiornamento dei Clusters con " << iterations << " iterazioni in: " << duration << "s\n";
        try {
            drawChartPoint(points, nPoint);
        } catch (int e) {
            cout << "Errore generazione grafico\n";
        }
    }
    if (SoA) {
        cout << "**********************Points in SoA************************\n";
        srand(time(NULL));
        double timeStart = omp_get_wtime();
        cout << "Creazione di " << nPoint << " punti casuali\n";
        struct pointArray points;
        initPointArray(&points, nPoint);
        cout << "Creazione di " << nCluster << " Clusters\n";
        vector<Cluster> clusters = initCluster(nCluster);
        double end = omp_get_wtime();
        auto duration = end - timeStart;
        cout << "Punti e Clusters generati in: " << duration << "s\n";
        bool updated = true;
        int iterations = 0;
        while (updated && iterations < itr) {
            iterations++;
            computeDistancePointArray(&points, clusters, nPoint);
            updated = updateClusters(clusters);
        }
        double time = omp_get_wtime();
        duration = time - end;
        cout << "Aggiornamento dei Clusters con " << iterations << " iterazioni in: " << duration << "s\n";
        try {
            drawChartPointArray(&points, nPoint);
        } catch (int e) {
            cout << "Errore generazione grafico\n";
        }
    }
    return 0;
}

void initPoint(struct point *points, int numPoint) {
    for (int i = 0; i < numPoint; i++) {
        points[i].x = rand() % (int) Range;
        points[i].y = rand() % (int) Range;
    }
}

void initPointArray(struct pointArray *points, int numPoint) {
    for (int i = 0; i < numPoint; i++) {
        points->x[i] = rand() % (int) Range;
        points->y[i] = rand() % (int) Range;
    }
}

vector<Cluster> initCluster(int numCluster) {
    vector<Cluster> clusters(numCluster);
    Cluster *cluster = &clusters[0];
    for (int i = 0; i < numCluster; i++) {
        Cluster *c = new Cluster(rand() % (int) Range, rand() % (int) Range);
        cluster[i] = *c;
    }
    return clusters;
}

void computeDistancePoint(struct point *points, vector<Cluster> &clusters, int nPoint) {
    unsigned long clustersSize = clusters.size();
    double minDistance;
    int minIndex;
    for (int i = 0; i < nPoint; i++) {
        minDistance = euclideanDistPoint(points[i], clusters[0]);
        minIndex = 0;
        for (int j = 1; j < clustersSize; j++) {
            Cluster &cluster = clusters[j];
            double distance = euclideanDistPoint(points[i], cluster);
            if (distance < minDistance) {
                minDistance = distance;
                minIndex = j;
            }
        }
        points[i].clusterID = minIndex;
        clusters[minIndex].addPoint(points[i].x, points[i].y);
    }
}

void computeDistancePointArray(struct pointArray *points, vector<Cluster> &clusters, int nPoint) {
    unsigned long clustersSize = clusters.size();
    double minDistance;
    int minIndex;
    for (int i = 0; i < nPoint; i++) {
        minDistance = euclideanDistPointArray(points->x[i], points->y[i], clusters[0]);
        minIndex = 0;
        for (int j = 1; j < clustersSize; j++) {
            Cluster &cluster = clusters[j];
            double distance = euclideanDistPointArray(points->x[i], points->y[i], cluster);
            if (distance < minDistance) {
                minDistance = distance;
                minIndex = j;
            }
        }
        points->clusterID[i] = minIndex;
        clusters[minIndex].addPoint(points->x[i], points->y[i]);
    }
}

double euclideanDistPoint(struct point p, Cluster c) {
    double dist = sqrt(pow(p.x - c.getX(), 2) + pow(p.y - c.getY(), 2));
    return dist;
}

double euclideanDistPointArray(double x, double y, Cluster c) {
    double dist = sqrt(pow(x - c.getX(), 2) + pow(y - c.getY(), 2));
    return dist;
}

bool updateClusters(vector<Cluster> &clusters) {
    bool updated = false;
    for (int i = 0; i < clusters.size(); i++) {
        updated = clusters[i].update();
        clusters[i].freePoint();
    }
    return updated;
}

void drawChartPoint(struct point *points, int nPoint) {
    ofstream outfile("dataPoint.txt");
    for (int i = 0; i < nPoint; i++) {
        outfile << points[i].x << " " << points[i].y << " " << points[i].clusterID << std::endl;
    }
    outfile.close();
    system("gnuplot -p -e \"plot 'dataPoint.txt' using 1:2:3 with points pt 7 ps 1 palette notitle \"");
    remove("dataPoint.txt");
}

void drawChartPointArray(struct pointArray *points, int nPoint) {
    ofstream outfile("dataPointArray.txt");
    for (int i = 0; i < nPoint; i++) {
        outfile << points->x[i] << " " << points->y[i] << " " << points->clusterID[i] << std::endl;
    }
    outfile.close();
    system("gnuplot -p -e \"plot 'dataPointArray.txt' using 1:2:3 with points pt 7 ps 1 palette notitle \"");
    remove("dataPointArray.txt");
}
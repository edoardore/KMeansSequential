#ifndef KMEANSOPENMP_CLUSTER_H
#define KMEANSOPENMP_CLUSTER_H

class Cluster {
public:
    Cluster(double x, double y) {
        newX = 0;
        newY = 0;
        size = 0;
        this->x = x;
        this->y = y;
    }

    Cluster() {
        newX = 0;
        newY = 0;
        x = 0;
        y = 0;
        size = 0;
    }

    void addPoint(double x, double y) {
        newX += x;
        newY += y;
        size++;
    }

    void freePoint() {
        size = 0;
        newX = 0;
        newY = 0;
    };

    double getX() {
        return this->x;
    }

    double getY() {
        return this->y;
    }

    bool update() {
        if (x == newX / size && y == newY / size) {
            return false;
        }
        x = newX / size;
        y = newY / size;
        return true;
    }

private:
    double x;
    double y;
    double newX;
    double newY;
    int size;
};


#endif //KMEANSOPENMP_CLUSTER_H

#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QVector>
#include "point3d.h"

class Node {
public:
    Node(const Point3D pt);
    void addTriangle(const int triangleIndex);
    int getTriangle(const int index);
    void addNeighbour(const int nodeIndex);
    Point3D pt() const;
    int nb_triangles() const;
    int nb_neighbours() const;

    QString toString() const;
    QString toMeshString() const;
private:
    int _nb_triangles, _nb_neighbours;
    QVector<int> _triangles, _neighbours;
    Point3D _pt;
};

#endif // NODE_H

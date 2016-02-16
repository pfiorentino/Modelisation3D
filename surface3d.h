#ifndef SURFACE3D_H
#define SURFACE3D_H

#include <QVector>
#include <math.h>
#include "triangle.h"
#include "vertice.h"

class Surface3D
{
public:
    Surface3D(QString meshFileName);
    void addVertice(Vertice* vertice);
    void addTriangle(Triangle* triangle);
    void addAllTriangles(const QVector<Triangle*> triangles);
    const Vertice computeNormal(int facetIndex);
    const Surface3D resize(const float factor);
    const Vertice computeNodeNormal(int nodeIndex);
    const Vertice getMin();
    const Vertice getMax();
    int getNbNodes() const;
    Vertice* getNode(const int nodeIndex) const;
    int getNbTriangles() const;
    Triangle* getTriangle(const int facetIndex) const;
    QString getMeshFileName() const;

private:
    int _nb_nodes, _nb_facets;
    QString _meshFileName;
    QVector<Triangle*> _facetsList;
    QVector<Vertice*> _nodesList;
};

#endif // SURFACE3D_H

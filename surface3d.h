#ifndef SURFACE3D_H
#define SURFACE3D_H

#include <QVector>
#include "triangle.h"
#include "vertice.h"

class Surface3D
{
public:
    Surface3D();
    void addVertice(Vertice* vertice);
    void addTriangle(Triangle* triangle);
    const Vertice computeNormal(int facetIndex);
    const Vertice computeNodeNormal(int nodeIndex);
    const Vertice getMin();
    const Vertice getMax();
    int getNbNodes();
private:
    int _nb_nodes, _nb_facets;
    QVector<Triangle*> _facetsList;
    QVector<Vertice*> _nodesList;
};

#endif // SURFACE3D_H

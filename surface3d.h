#ifndef SURFACE3D_H
#define SURFACE3D_H

#include <QVector>
#include <QFile>
#include <QTextStream>
#include <math.h>
#include "triangle.h"
#include "node.h"

class Surface3D
{
public:
    Surface3D(const QString meshFileName);
    void addNode(Node* node);
    void addTriangle(Triangle* triangle);
    void addAllTriangles(const QVector<Triangle*> triangles);
    const Point3D computeNormal(int facetIndex);
    const Surface3D resize(const float factor);
    const Point3D computeNodeNormal(int nodeIndex);
    const Point3D getMin();
    const Point3D getMax();
    int getNbNodes() const;
    Node* getNode(const int nodeIndex) const;
    int getNbTriangles() const;
    Triangle* getTriangle(const int facetIndex) const;
    QString getMeshFileName() const;
    float getAverageNeighbours() const;
    float getAverageTriangles() const;

    void saveSurfaceFile(const QString savePath) const;
    static Surface3D parseSurfaceFile(const QString filePath, const QString meshFileName);

private:
    int _nb_nodes, _nb_facets;
    QString _meshFileName;
    QVector<Triangle*> _facetsList;
    QVector<Node*> _nodesList;
};

#endif // SURFACE3D_H

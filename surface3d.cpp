#include "surface3d.h"
#include <QDebug>

Surface3D::Surface3D(QString meshFileName):
    _nb_nodes(0), _nb_facets(0), _meshFileName(meshFileName)
{
}

void Surface3D::addVertice(Vertice* vertice) {
    _nodesList.append(vertice);
    ++_nb_nodes;
}

void Surface3D::addTriangle(Triangle* triangle) {
    _facetsList.append(triangle);
    ++_nb_facets;
}

void Surface3D::addAllTriangles(const QVector<Triangle*> triangles) {
    for (int i = 0; i < triangles.size(); i++){
        _facetsList.append(triangles[i]->copy());
        ++_nb_facets;
    }
}

const Vertice Surface3D::computeNormal(int facetIndex) {
    if (_facetsList.size() > facetIndex) {
        Triangle* facet = _facetsList[facetIndex];

        if (_nodesList.size() >= facet->getP1() &&
            _nodesList.size() >= facet->getP2() &&
            _nodesList.size() >= facet->getP3()){

            Vertice* _p1 = _nodesList[facet->getP1()-1];
            Vertice* _p2 = _nodesList[facet->getP2()-1];
            Vertice* _p3 = _nodesList[facet->getP3()-1];

            float _x, _y, _z;
            _x = (_p2->getY()-_p1->getY())*(_p3->getZ()-_p1->getZ())-(_p2->getZ()-_p1->getZ())*(_p3->getY()-_p1->getY());
            _y = (_p2->getZ()-_p1->getZ())*(_p3->getX()-_p1->getX())-(_p2->getX()-_p1->getX())*(_p3->getZ()-_p1->getZ());
            _z = (_p2->getX()-_p1->getX())*(_p3->getY()-_p1->getY())-(_p2->getY()-_p1->getY())*(_p3->getX()-_p1->getX());

            return Vertice(_x, _y, _z);
        } else {
            throw "computeNormal: Out of bounds nodeIndex";
        }
    } else {
        throw "computeNormal: Out of bounds facetIndex";
    }
}

const Surface3D Surface3D::resize(const float factor) {
    Surface3D resizedSurface("resized_"+_meshFileName);
    resizedSurface.addAllTriangles(_facetsList);

    for (int i = 0; i < getNbNodes(); ++i) {
        try {
            Vertice normalizedVertice = computeNodeNormal(i+1);

            float vectorSize = sqrt(pow(normalizedVertice.getX(), 2.0)+pow(normalizedVertice.getY(), 2.0)+pow(normalizedVertice.getZ(), 2.0));

            Vertice* newVertice = new Vertice(_nodesList[i]->getX()+factor*(normalizedVertice.getX()/vectorSize),
                                              _nodesList[i]->getY()+factor*(normalizedVertice.getY()/vectorSize),
                                              _nodesList[i]->getZ()+factor*(normalizedVertice.getZ()/vectorSize));

            resizedSurface.addVertice(newVertice);
        } catch (const char * Msg) {
            qDebug() << Msg;
        }
    }

    return resizedSurface;
}

const Vertice Surface3D::computeNodeNormal(int nodeIndex) {
    int _facetsCount = 0;
    float _x = 0, _y = 0, _z = 0;
    for (int i = 0; i < _facetsList.size(); i++){
        if (_facetsList[i]->isVertice(nodeIndex)){
            Vertice tmp = computeNormal(i);
            _x += tmp.getX();
            _y += tmp.getY();
            _z += tmp.getZ();
            _facetsCount++;
        }
    }

    return Vertice(_x/_facetsCount, _y/_facetsCount, _z/_facetsCount);
}

const Vertice Surface3D::getMin(){
    float _xMin = std::numeric_limits<float>::max(),
          _yMin = std::numeric_limits<float>::max(),
          _zMin = std::numeric_limits<float>::max();

    for (int i = 0; i < _nodesList.size(); i++){
        if (_nodesList[i]->getX() < _xMin){
            _xMin = _nodesList[i]->getX();
        }

        if (_nodesList[i]->getY() < _yMin){
            _yMin = _nodesList[i]->getY();
        }

        if (_nodesList[i]->getZ() < _zMin){
            _zMin = _nodesList[i]->getZ();
        }
    }

    return Vertice(_xMin, _yMin, _zMin);
}

const Vertice Surface3D::getMax(){
    float _xMax = std::numeric_limits<float>::min(),
          _yMax = std::numeric_limits<float>::min(),
          _zMax = std::numeric_limits<float>::min();

    for (int i = 0; i < _nodesList.size(); i++){
        if (_nodesList[i]->getX() > _xMax){
            _xMax = _nodesList[i]->getX();
        }

        if (_nodesList[i]->getY() > _yMax){
            _yMax = _nodesList[i]->getY();
        }

        if (_nodesList[i]->getZ() > _zMax){
            _zMax = _nodesList[i]->getZ();
        }
    }

    return Vertice(_xMax, _yMax, _zMax);
}

int Surface3D::getNbNodes() const {
    return _nodesList.size();
}

Vertice* Surface3D::getNode(const int nodeIndex) const {
    return _nodesList[nodeIndex];
}

int Surface3D::getNbTriangles() const {
    return _facetsList.size();
}

Triangle* Surface3D::getTriangle(const int facetIndex) const {
    return _facetsList[facetIndex];
}

QString Surface3D::getMeshFileName() const
{
    return _meshFileName;
}



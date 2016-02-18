#include "surface3d.h"
#include <iostream>
#include <QDebug>

using namespace std;

Surface3D::Surface3D(const QString meshFileName):
    _nb_nodes(0), _nb_facets(0), _meshFileName(meshFileName)
{
}

void Surface3D::addNode(Node* node) {
    _nodesList.append(node);
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

const Point3D Surface3D::computeNormal(int facetIndex) {
    if (_facetsList.size() > facetIndex) {
        Triangle* facet = _facetsList[facetIndex];

        if (_nodesList.size() > facet->getP1() &&
            _nodesList.size() > facet->getP2() &&
            _nodesList.size() > facet->getP3()){

            Point3D _p1 = _nodesList[facet->getP1()]->pt();
            Point3D _p2 = _nodesList[facet->getP2()]->pt();
            Point3D _p3 = _nodesList[facet->getP3()]->pt();

            float _x, _y, _z;
            _x = (_p2.y()-_p1.y())*(_p3.z()-_p1.z())-(_p2.z()-_p1.z())*(_p3.y()-_p1.y());
            _y = (_p2.z()-_p1.z())*(_p3.x()-_p1.x())-(_p2.x()-_p1.x())*(_p3.z()-_p1.z());
            _z = (_p2.x()-_p1.x())*(_p3.y()-_p1.y())-(_p2.y()-_p1.y())*(_p3.x()-_p1.x());

            return Point3D(_x, _y, _z);
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
            Point3D normalizedVertice = computeNodeNormal(i);

            float vectorSize = sqrt(pow(normalizedVertice.x(), 2.0)+pow(normalizedVertice.y(), 2.0)+pow(normalizedVertice.z(), 2.0));

            Point3D newVertice(_nodesList[i]->pt().x()+factor*(normalizedVertice.x()/vectorSize),
                               _nodesList[i]->pt().y()+factor*(normalizedVertice.y()/vectorSize),
                               _nodesList[i]->pt().z()+factor*(normalizedVertice.z()/vectorSize));

            resizedSurface.addNode(new Node(newVertice));
        } catch (const char * Msg) {
            qDebug() << Msg;
        }
    }

    return resizedSurface;
}

const Point3D Surface3D::computeNodeNormal(int nodeIndex) {
    float _x = 0, _y = 0, _z = 0;

    Node* node = getNode(nodeIndex);
    for (int i = 0; i < node->nb_triangles(); ++i){
        Point3D tmp = computeNormal(node->getTriangle(i));
        _x += tmp.x();
        _y += tmp.y();
        _z += tmp.z();
    }

    return Point3D(_x/node->nb_triangles(), _y/node->nb_triangles(), _z/node->nb_triangles());
}

const Point3D Surface3D::getMin(){
    float _xMin = std::numeric_limits<float>::max(),
          _yMin = std::numeric_limits<float>::max(),
          _zMin = std::numeric_limits<float>::max();

    for (int i = 0; i < _nodesList.size(); i++){
        if (_nodesList[i]->pt().x() < _xMin){
            _xMin = _nodesList[i]->pt().x();
        }

        if (_nodesList[i]->pt().y() < _yMin){
            _yMin = _nodesList[i]->pt().y();
        }

        if (_nodesList[i]->pt().z() < _zMin){
            _zMin = _nodesList[i]->pt().z();
        }
    }

    return Point3D(_xMin, _yMin, _zMin);
}

const Point3D Surface3D::getMax(){
    float _xMax = std::numeric_limits<float>::min(),
          _yMax = std::numeric_limits<float>::min(),
          _zMax = std::numeric_limits<float>::min();

    for (int i = 0; i < _nodesList.size(); i++){
        if (_nodesList[i]->pt().x() > _xMax){
            _xMax = _nodesList[i]->pt().x();
        }

        if (_nodesList[i]->pt().y() > _yMax){
            _yMax = _nodesList[i]->pt().y();
        }

        if (_nodesList[i]->pt().z() > _zMax){
            _zMax = _nodesList[i]->pt().z();
        }
    }

    return Point3D(_xMax, _yMax, _zMax);
}

int Surface3D::getNbNodes() const {
    return _nb_nodes;
}

Node* Surface3D::getNode(const int nodeIndex) const {
    return _nodesList[nodeIndex];
}

int Surface3D::getNbTriangles() const {
    return _nb_facets;
}

Triangle* Surface3D::getTriangle(const int facetIndex) const {
    return _facetsList[facetIndex];
}

QString Surface3D::getMeshFileName() const
{
    return _meshFileName;
}

float Surface3D::getAverageNeighbours() const {
    int neighboursSum = 0;
    for (int i = 0; i < getNbNodes(); ++i) {
        neighboursSum += getNode(i)->nb_neighbours();
    }

    return (float) neighboursSum/(float) getNbNodes();
}

float Surface3D::getAverageTriangles() const {
    int trianglesSum = 0;
    for (int i = 0; i < getNbNodes(); ++i) {
        trianglesSum += getNode(i)->nb_triangles();
    }

    return (float) trianglesSum/(float) getNbNodes();
}

Surface3D Surface3D::parseSurfaceFile(const QString filePath, const QString meshFileName) {
    Surface3D surface = Surface3D(meshFileName);

    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine().simplified();

            if (line == "Vertices") {
                int verticesCount = in.readLine().simplified().toInt();

                for (int i = 0; i < verticesCount; i++){
                    QStringList splittedLine = in.readLine().simplified().split(" ");
                    if (splittedLine.count() == 4){
                        Node* node = new Node(Point3D(splittedLine[0].toFloat(), splittedLine[1].toFloat(), splittedLine[2].toFloat()));
                        surface.addNode(node);
                    } else {
                        qWarning() << "Invalid vertex format";
                    }
                }
            }

            if (line == "Triangles") {
                int trianglesCount = in.readLine().simplified().toInt();

                for (int i = 0; i < trianglesCount; i++){
                    QStringList splittedLine = in.readLine().simplified().split(" ");
                    if (splittedLine.count() == 4){
                        Triangle* triangle = new Triangle(splittedLine[0].toInt()-1, splittedLine[1].toInt()-1, splittedLine[2].toInt()-1);
                        surface.addTriangle(triangle);

                        surface.getNode(triangle->getP1())->addTriangle(i);
                        surface.getNode(triangle->getP2())->addTriangle(i);
                        surface.getNode(triangle->getP3())->addTriangle(i);

                        surface.getNode(triangle->getP1())->addNeighbour(triangle->getP2());
                        surface.getNode(triangle->getP1())->addNeighbour(triangle->getP3());

                        surface.getNode(triangle->getP2())->addNeighbour(triangle->getP1());
                        surface.getNode(triangle->getP2())->addNeighbour(triangle->getP3());

                        surface.getNode(triangle->getP3())->addNeighbour(triangle->getP1());
                        surface.getNode(triangle->getP3())->addNeighbour(triangle->getP2());
                    } else {
                        qWarning() << "Invalid triangle format";
                    }
                }
            }
        }
        inputFile.close();
    } else {
        cout << "Can't open file" << endl;
    }

    return surface;
}

void Surface3D::saveSurfaceFile(const QString savePath) const {
    QFile outputFile(savePath+getMeshFileName());

    if (outputFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&outputFile);
        out << "MeshVersionFormatted 1" << endl;
        out << "Dimension" << endl;
        out << "3" << endl;
        out << "Vertices" << endl;
        out << getNbNodes() << endl;
        for (int i = 0; i < getNbNodes(); i++) {
            out << getNode(i)->toMeshString() << endl;
        }

        out << "Triangles" << endl;
        out << getNbTriangles() << endl;
        for (int i = 0; i < getNbTriangles(); i++) {
            out << getTriangle(i)->toMeshString() << endl;
        }

        out << "End" << endl;
        out.flush();
        outputFile.close();
    }
}


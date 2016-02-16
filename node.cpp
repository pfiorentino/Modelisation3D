#include "node.h"

Node::Node(const Point3D pt):
    _nb_triangles(0), _nb_neighbours(0), _pt(pt)
{

}

void Node::addTriangle(const int triangleIndex){
    _triangles.append(triangleIndex);
    ++_nb_triangles;
}

int Node::getTriangle(const int index){
    return _triangles[index];
}

void Node::addNeighbour(const int nodeIndex){
    if (!_neighbours.contains(nodeIndex)){
        _neighbours.append(nodeIndex);
        ++_nb_neighbours;
    }
}

Point3D Node::pt() const
{
    return _pt;
}

QString Node::toString() const {
    return "Node(" + QString::number(_pt.x()) + ", " + QString::number(_pt.y()) + ", " + QString::number(_pt.z()) + ")";
}

QString Node::toMeshString() const {
    return QString::number(_pt.x()) + " " + QString::number(_pt.y()) + " " + QString::number(_pt.z()) + " 0";
}

int Node::nb_triangles() const
{
    return _nb_triangles;
}

int Node::nb_neighbours() const
{
    return _nb_neighbours;
}

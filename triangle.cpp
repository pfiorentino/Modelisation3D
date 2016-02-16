#include "triangle.h"

Triangle::Triangle(const int p1, const int p2, const int p3):
    _p1(p1), _p2(p2), _p3(p3)
{

}

bool Triangle::isVertice(const int verticeIndex){
    return verticeIndex == _p1 || verticeIndex == _p2 || verticeIndex == _p3;
}

QString Triangle::toMeshString() const {
    return QString::number(_p1) + " " + QString::number(_p2) + " " + QString::number(_p3) + " 508";
}

Triangle* Triangle::copy() const {
    return new Triangle(_p1, _p2, _p3);
}

int Triangle::getP1() {
    return _p1;
}

int Triangle::getP2() {
    return _p2;
}

int Triangle::getP3() {
    return _p3;
}

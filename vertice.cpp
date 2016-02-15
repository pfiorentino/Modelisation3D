#include "vertice.h"

Vertice::Vertice(const float x, const float y, const float z):
    _x(x), _y(y), _z(z)
{

}

QString Vertice::toString() const {
    return "Vertice(" + QString::number(_x) + ", " + QString::number(_y) + ", " + QString::number(_z) + ")";
}

float Vertice::getX() {
    return _x;
}

float Vertice::getY() {
    return _y;
}

float Vertice::getZ() {
    return _z;
}

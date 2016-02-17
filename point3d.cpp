#include "point3d.h"

Point3D::Point3D(const float x, const float y, const float z):
    _x(x), _y(y), _z(z)
{

}

QString Point3D::toString() const {
    return "Point3D(" + QString::number(_x) + ", " + QString::number(_y) + ", " + QString::number(_z) + ")";
}

QString Point3D::toMeshString() const {
    return QString::number(_x) + " " + QString::number(_y) + " " + QString::number(_z) + " 0";
}

float Point3D::x() const
{
    return _x;
}

float Point3D::y() const
{
    return _y;
}

float Point3D::z() const
{
    return _z;
}

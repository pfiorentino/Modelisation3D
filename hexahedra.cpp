#include "hexahedra.h"

Hexahedra::Hexahedra(Point3D origin, int nx, int ny):
    _nx(nx+1), _ny(ny+1)
{
    _points.append(getVerticeIndex(origin.x(), origin.y(), origin.z()));
    _points.append(getVerticeIndex(origin.x(), origin.y(), origin.z()+1));
    _points.append(getVerticeIndex(origin.x()+1, origin.y(), origin.z()+1));
    _points.append(getVerticeIndex(origin.x()+1, origin.y(), origin.z()));

    _points.append(getVerticeIndex(origin.x(), origin.y()+1, origin.z()));
    _points.append(getVerticeIndex(origin.x(), origin.y()+1, origin.z()+1));
    _points.append(getVerticeIndex(origin.x()+1, origin.y()+1, origin.z()+1));
    _points.append(getVerticeIndex(origin.x()+1, origin.y()+1, origin.z()));
}

QString Hexahedra::toMeshString() const {
    QString result = "";
    for (int i = 0; i < 8; ++i) {
        result += QString::number(_points[i]+1)+" ";
    }
    return result+"508";
}

int Hexahedra::getVerticeIndex(const int x, const int y, const int z) const {
    return x+_nx*y+_nx*_ny*z;
}

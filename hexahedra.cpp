#include "hexahedra.h"

Hexahedra::Hexahedra()
{
}

void Hexahedra::addPoint(int point) {
    _points.append(point);
}

QString Hexahedra::toMeshString() const {
    QString result = "";
    for (int i = 0; i < 8; ++i) {
        result += QString::number(_points[i]+1)+" ";
    }
    return result+"508";
}

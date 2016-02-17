#include "hexaedra.h"

Hexaedra::Hexaedra()
{
}

void Hexaedra::addPoint(int point) {
    _points.append(point);
}

QString Hexaedra::toMeshString() const {
    QString result = "";
    for (int i = 0; i < 8; ++i) {
        result += QString::number(_points[i]+1)+" ";
    }
    return result+"508";
}

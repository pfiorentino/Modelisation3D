#ifndef HEXAEDRA_H
#define HEXAEDRA_H

#include <QString>
#include <QVector>
#include "point3d.h"

class Hexahedra {
public:
    Hexahedra(Point3D origin, int nx, int ny);
    QString toMeshString() const;
private:
    int _nx, _ny;
    QVector<int> _points;
    int getVerticeIndex(const int x, const int y, const int z) const;
};

#endif // HEXAEDRA_H

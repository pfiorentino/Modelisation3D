#ifndef GRID3D_H
#define GRID3D_H

#include "point3d.h"
#include "hexahedra.h"
#include <QString>
#include <QFile>

class Grid3D
{
public:
    Grid3D(const Point3D origin, const int nx, const int ny, const int nz);
    int getNbNodes() const;
    int getNbHexahedra() const;

    void saveGridFile(const QString filePath) const;
private:
    Point3D _origin;
    int _nx, _ny, _nz;
};

#endif // GRID3D_H

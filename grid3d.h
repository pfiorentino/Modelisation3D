#ifndef GRID3D_H
#define GRID3D_H

#include <QString>
#include <QFile>
#include <QVector>

#include "point3d.h"
#include "hexahedra.h"
#include "sphere.h"

class Grid3D {
public:
    Grid3D(const Point3D origin, const int nx, const int ny, const int nz);
    int getNbNodes() const;
    int getNbHexahedra() const;

    void saveGridFile(const QString filePath) const;
    float getProp(int index) const;
    void setProp(int index, float value);
    void setPropsValues(const ImplicitObject &object);

    int getVerticeIndex(const Point3D &pt) const;
    Point3D* getIntersectValue(const Point3D &pt1, const float dist1, const Point3D &pt2, const float dist2);
    void writeIntersect(const QString filePath) const;
private:
    Point3D _origin;
    int _nx, _ny, _nz;
    QVector<float> _props;
    QVector<Point3D*> _intersect;
};

#endif // GRID3D_H

#ifndef POINT3D_H
#define POINT3D_H

#include <QString>
#include <math.h>

class Point3D
{
public:
    Point3D(const float x, const float y, const float z);
    float x() const;
    float y() const;
    float z() const;

    float getDistance(const Point3D &pt) const;

    QString toString() const;
    QString toMeshString() const;
private:
    const float _x, _y, _z;
};

#endif // POINT3D_H

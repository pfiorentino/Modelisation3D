#ifndef POINTS_H
#define POINTS_H

#include "implicitobject.h"
#include "point3d.h"
#include <QVector>

class Points : public ImplicitObject
{
public:
    Points();
    virtual float getDistance(const Point3D& pt) const;
public:
    QVector<Point3D> _points;
};

#endif // POINTS_H

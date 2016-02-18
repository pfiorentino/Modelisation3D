#ifndef IMPLICITOBJECT_H
#define IMPLICITOBJECT_H

#include "point3d.h"

class ImplicitObject
{
public:
    ImplicitObject();
    virtual float getDistance(const Point3D &pt) const = 0;
};

#endif // IMPLICITOBJECT_H

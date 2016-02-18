#ifndef SPHERE_H
#define SPHERE_H

#include "point3d.h"
#include "implicitobject.h"
#include <math.h>

class Sphere : public ImplicitObject
{
public:
    Sphere(const Point3D &center, const int radius);
    virtual float getDistance(const Point3D& pt) const;
private:
    Point3D _center;
    float _radius;
};

#endif // SPHERE_H

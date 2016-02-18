#ifndef DOUBLESPHERE_H
#define DOUBLESPHERE_H

#include "implicitobject.h"
#include "sphere.h"

class DoubleSphere : public ImplicitObject
{
public:
    DoubleSphere(const Sphere &s1, const Sphere &s2);
    virtual float getDistance(const Point3D& pt) const;
private:
    Sphere _sphere1;
    Sphere _sphere2;

};

#endif // DOUBLESPHERE_H

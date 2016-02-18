#ifndef NSPHERE_H
#define NSPHERE_H

#include <QVector>
#include "sphere.h"

class NSphere : public ImplicitObject
{
public:
    NSphere();
    virtual float getDistance(const Point3D& pt) const;
    void addSphere(Sphere* s);
private:
    QVector<Sphere*> _spheres;
};

#endif // NSPHERE_H

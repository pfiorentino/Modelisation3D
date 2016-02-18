#include "doublesphere.h"
#include <math.h>

DoubleSphere::DoubleSphere(const Sphere &s1, const Sphere &s2):
    _sphere1(s1), _sphere2(s2)
{

}

float DoubleSphere::getDistance(const Point3D &pt) const {
    return fmin(_sphere1.getDistance(pt), _sphere2.getDistance(pt));
}

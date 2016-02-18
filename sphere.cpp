#include "sphere.h"

Sphere::Sphere(const Point3D &center, const int radius):
    _center(center), _radius(radius)
{

}

float Sphere::getDistance(const Point3D &pt) const
{
    return sqrt(pow(pt.x()-_center.x(), 2.0)+pow(pt.y()-_center.y(), 2.0)+pow(pt.z()-_center.z(), 2.0))-_radius;
}

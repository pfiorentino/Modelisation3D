#ifndef LAYOUT_H
#define LAYOUT_H

#include "point3d.h"
#include "implicitobject.h"

class Layout : public ImplicitObject
{
public:
    Layout(const float a, const float b, const float c, const float d);
    virtual float getDistance(const Point3D& pt) const;
private:
    float _a, _b, _c, _d;
};

#endif // LAYOUT_H

#include "layout.h"
#include <math.h>

Layout::Layout(const float a, const float b, const float c, const float d):
    _a(a), _b(b), _c(c), _d(d)
{

}

float Layout::getDistance(const Point3D &pt) const {
    if (_a == 0 && _b == 0 && _c == 0) {
        return 1;
    } else {
        return fabs(_a*pt.x()+_b*pt.y()+_c*pt.z()-_d)/sqrt(pow(_a, 2.0)+pow(_b, 2.0)+pow(_c, 2.0));
    }
}

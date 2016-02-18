#include "nsphere.h"
#include <math.h>

NSphere::NSphere()
{

}

float NSphere::getDistance(const Point3D &pt) const {
    float dist = std::numeric_limits<float>::max();

    for (int i = 0; i < _spheres.size(); i++){
        dist = fmin(dist, _spheres[i]->getDistance(pt));
    }

    return dist;
}

void NSphere::addSphere(Sphere* s) {
    _spheres.append(s);
}

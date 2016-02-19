#include "points.h"

Points::Points()
{

}

float Points::getDistance(const Point3D &pt) const {
    float distance = 0;

    for (int i = 0; i < _points.size(); ++i) {
        float newDistance = _points[i].getDistance(pt);
        if (distance > newDistance){
            distance = newDistance;
        }
    }

    return distance;
}

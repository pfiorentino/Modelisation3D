#ifndef VERTICE_H
#define VERTICE_H

#include <QString>

class Vertice
{
public:
    Vertice(const float x, const float y, const float z);
    QString toString() const;
    float getX();
    float getY();
    float getZ();
private:
    const float _x, _y, _z;
};

#endif // VERTICE_H

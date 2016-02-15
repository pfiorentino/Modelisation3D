#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle
{
public:
    Triangle(const int p1, const int p2, const int p3);
    bool isVertice(const int verticeIndex);

    int getP1();
    int getP2();
    int getP3();
private:
    int _p1, _p2, _p3;
};

#endif // TRIANGLE_H

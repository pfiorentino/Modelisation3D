#ifndef HEXAEDRA_H
#define HEXAEDRA_H

#include <QString>
#include <QVector>

class Hexaedra
{
public:
    Hexaedra();
    void addPoint(int point);
    QString toMeshString() const;
private:
    QVector<int> _points;
};

#endif // HEXAEDRA_H

#include "grid3d.h"
#include <iostream>
#include <QDebug>
#include <QVector>

using namespace std;

Grid3D::Grid3D(const Point3D origin, const int nx, const int ny, const int nz):
    _origin(origin), _nx(nx), _ny(ny), _nz(nz)
{

}

int Grid3D::getNbNodes() const
{
    return (_nx+1)*(_ny+1)*(_nz+1);
}

int Grid3D::getNbHexahedra() const
{
    return _nx*_ny*_nz;
}

void Grid3D::saveGridFile(const QString filePath) const {
    QFile outputFile(filePath);

    if (outputFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&outputFile);
        out << "MeshVersionFormatted 1" << endl;
        out << "Dimension" << endl;
        out << "3" << endl;
        out << "Vertices" << endl;
        out << getNbNodes() << endl;

        QVector<Hexahedra*> hexs;
        for (int k = 0; k <= _nz; ++k) {
            for (int j = 0; j <= _ny; ++j) {
                for (int i = 0; i <= _nx; ++i) {
                    Point3D tmpPoint(i+_origin.x(), j+_origin.y(), k+_origin.z());
                    out << tmpPoint.toMeshString() << endl;

                    if (k != _nz && j != _ny && i != _nx){
                        Hexahedra* hex = new Hexahedra(Point3D(i, j, k), _nx, _ny);
                        hexs.append(hex);
                    }
                }
            }
        }

        out << "Hexahedra" << endl;
        out << getNbHexahedra() << endl;

        for (int i = 0; i < hexs.size(); ++i) {
            out << hexs[i]->toMeshString() << endl;
        }

        out << "End" << endl;
        out.flush();
        outputFile.close();
    }
}

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

int Grid3D::getNbHexahedras() const
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

        QVector<Point3D*> points;
        for (int k = _origin.z(); k < _origin.z()+_nz+1; ++k) {
            for (int j = _origin.y(); j < _origin.y()+_ny+1; ++j) {
                for (int i = _origin.x(); i < _origin.x()+_nx+1; ++i) {
                    Point3D* tmpPoint = new Point3D(i, j, k);
                    points.append(tmpPoint);
                    out << tmpPoint->toMeshString() << endl;
                }
            }
        }


        out << "Hexahedra" << endl;
        out << getNbHexahedras() << endl;

        int nnx = _nx+1, nny = _ny+1;
        for (int k = 0; k < _nz; ++k) {
            for (int j = 0; j < _ny; ++j) {
                for (int i = 0; i < _nx; ++i) {

                    Hexahedra hex;
                    hex.addPoint(i+nnx*j+nnx*nny*k);
                    hex.addPoint(i+nnx*j+nnx*nny*(k+1));
                    hex.addPoint((i+1)+nnx*j+nnx*nny*(k+1));
                    hex.addPoint((i+1)+nnx*j+nnx*nny*k);

                    hex.addPoint(i+nnx*(j+1)+nnx*nny*k);
                    hex.addPoint(i+nnx*(j+1)+nnx*nny*(k+1));
                    hex.addPoint((i+1)+nnx*(j+1)+nnx*nny*(k+1));
                    hex.addPoint((i+1)+nnx*(j+1)+nnx*nny*k);

                    out << hex.toMeshString() << endl;
                }
            }
        }

        out << "End" << endl;
        out.flush();
        outputFile.close();
    }
}

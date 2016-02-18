#include "grid3d.h"
#include <iostream>
#include <QDebug>
#include <QVector>

using namespace std;

Grid3D::Grid3D(const Point3D origin, const int nx, const int ny, const int nz):
    _origin(origin), _nx(nx), _ny(ny), _nz(nz) {
    _props.resize(getNbNodes());
}

int Grid3D::getNbNodes() const {
    return (_nx+1)*(_ny+1)*(_nz+1);
}

int Grid3D::getNbHexahedra() const {
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

float Grid3D::getProp(int index) const {
    return _props.value(index, std::numeric_limits<float>::max());
}

void Grid3D::setProp(int index, float value) {
    _props.insert(index, value);
}

void Grid3D::setPropsValues(const ImplicitObject &object) {
    for (int k = _origin.z(); k <= _nz+_origin.z(); ++k) {
        for (int j = _origin.y(); j <= _ny+_origin.y(); ++j) {
            for (int i = _origin.x(); i <= _nx+_origin.x(); ++i) {
                Point3D pt(i, j, k);
                float dist = object.getDistance(pt);
                setProp(getVerticeIndex(pt), dist);
            }
        }
    }

    for (int k = _origin.z(); k < _nz+_origin.z(); ++k) {
        for (int j = _origin.y(); j < _ny+_origin.y(); ++j) {
            for (int i = _origin.x(); i < _nx+_origin.x(); ++i) {
                Point3D pt(i, j, k);
                float dist = getProp(getVerticeIndex(pt));

                Point3D ptx(i+1, j, k);
                float distx = getProp(getVerticeIndex(ptx));

                if (distx != 0 && dist/distx <= 0) {
                    _intersect.append(getIntersectValue(pt, dist, ptx, distx));
                }

                Point3D pty(i, j+1, k);
                float disty = getProp(getVerticeIndex(pty));

                if (disty != 0 && dist/disty <= 0) {
                    _intersect.append(getIntersectValue(pt, dist, pty, disty));
                }

                Point3D ptz(i, j, k+1);
                float distz = getProp(getVerticeIndex(ptz));

                if (distz != 0 && dist/distz <= 0) {
                    _intersect.append(getIntersectValue(pt, dist, ptz, distz));
                }
            }
        }
    }
}

int Grid3D::getVerticeIndex(const Point3D &pt) const {
    int nnx = _nx+1;
    int nny = _ny+1;
    return pt.x()+nnx*pt.y()+nnx*nny*pt.z();
}

Point3D* Grid3D::getIntersectValue(const Point3D &pt1, const float dist1, const Point3D &pt2, const float dist2)
{
    if (dist2 != 0 && dist1/dist2 <= 0) {
        float t = fabs(dist1/(dist1-dist2));
        return new Point3D((1-t)*pt1.x()+t*pt2.x(),
                           (1-t)*pt1.y()+t*pt2.y(),
                           (1-t)*pt1.z()+t*pt2.z());
    } else {
        throw "Incorrect dist values";
    }
}

void Grid3D::writeIntersect(const QString filePath) const
{
    QFile outputFile(filePath);

    if (outputFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&outputFile);
        out << "MeshVersionFormatted 1" << endl;
        out << "Dimension" << endl;
        out << "3" << endl;
        out << "Vertices" << endl;
        out << _intersect.size() << endl;

        for (int i = 0; i < _intersect.size(); ++i) {
            out << _intersect[i]->toMeshString() << endl;
        }

        out << "End" << endl;
        out.flush();
        outputFile.close();
    }
}

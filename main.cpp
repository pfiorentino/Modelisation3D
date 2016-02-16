#include <iostream>

#include <QDebug>

#include "surface3d.h"

using namespace std;

int main(int argc, char *argv[])
{
    QString meshesPath = "/Users/paul/Google Drive/Cours/Modelisation 3D/meshes/";
    QString meshName = "bunny.mesh";

    qDebug() << "\x1B[2J\x1B[H";

    Surface3D surface = Surface3D::parseSurfaceFile(meshesPath+meshName, meshName);
    cout << "Node 1 Normal:" << endl << surface.computeNodeNormal(1).toString().toStdString() << endl << endl;
    int random = rand() % surface.getNbNodes() + 1;
    cout << "Node random (" << random << ") Normal:" << endl << surface.computeNodeNormal(random).toString().toStdString() << endl << endl;

    cout << "Min:" << endl << surface.getMin().toString().toStdString() << endl << endl;
    cout << "Max:" << endl << surface.getMax().toString().toStdString() << endl << endl;

    cout << "Avg neighbours: " << QString::number(surface.getAverageNeighbours()).toStdString() << endl;
    cout << "Avg triangles: " << QString::number(surface.getAverageTriangles()).toStdString() << endl << endl;

    cout << "Generating resized surface..." << endl;
    Surface3D resizedSurface = surface.resize(0);
    resizedSurface.saveSurfaceFile(meshesPath);

    string command = "\"/Users/paul/Google Drive/Cours/Modelisation 3D/medit-osx\" \""+meshesPath.toStdString()+resizedSurface.getMeshFileName().toStdString()+"\"";
    system(command.c_str());

    return 0;
}



#include <iostream>

#include <QDebug>

#include "surface3d.h"
#include "grid3d.h"
#include "sphere.h"
#include "doublesphere.h"
#include "nsphere.h"

using namespace std;

void displayMesh(const string meshPath) {
    string command = "\"/Users/paul/Google Drive/Cours/Modelisation 3D/medit-osx\" \""+meshPath+"\" 1&>/dev/null";
    system(command.c_str());
}

int main(int argc, char *argv[]) {
    qDebug() << "\x1B[2J\x1B[H";

    QString meshesPath = "/Users/paul/Desktop/";

    int choice = 0;
    while (choice != 99) {
        cout << "Please choose an option: " << endl;
        cout << "1) Resize" << endl;
        cout << "2) Grid3D" << endl;
        cout << "3) Spheres" << endl;
        cout << "4) Cylinder" << endl;
        cout << "99) Exit" << endl << endl;
        cout << "choice: ";

        cin >> choice;

        switch (choice) {
            case 1: {
                QString meshesPath = "/Users/paul/Google Drive/Cours/Modelisation 3D/meshes/";
                QString meshName = "part.mesh";

                cout << "Computing \""+meshName.toStdString()+"\"" << endl << endl;

                Surface3D surface = Surface3D::parseSurfaceFile(meshesPath+meshName, meshName);
                cout << "Node 1 Normal:" << endl << surface.computeNodeNormal(1).toString().toStdString() << endl << endl;
                int random = rand() % surface.getNbNodes() + 1;
                cout << "Node random (" << random << ") Normal:" << endl << surface.computeNodeNormal(random).toString().toStdString() << endl << endl;

                cout << "Min:" << endl << surface.getMin().toString().toStdString() << endl << endl;
                cout << "Max:" << endl << surface.getMax().toString().toStdString() << endl << endl;

                cout << "Avg neighbours: " << QString::number(surface.getAverageNeighbours()).toStdString() << endl;
                cout << "Avg triangles: " << QString::number(surface.getAverageTriangles()).toStdString() << endl << endl;

                cout << "Generating resized surface..." << endl;
                Surface3D resizedSurface = surface.resize(-0.001);
                resizedSurface.saveSurfaceFile(meshesPath);

                displayMesh(meshesPath.toStdString()+resizedSurface.getMeshFileName().toStdString());
                break;
            }
            case 2: {
                cout << "Grid generation..." << endl << endl;
                Grid3D grid(Point3D(0, 0, 0), 50, 50, 50);

                grid.saveGridFile(meshesPath+"grid3D.mesh");

                displayMesh(meshesPath.toStdString()+"grid3D.mesh");
                break;
            }
            case 3: {
                cout << "Spheres generation..." << endl << endl;
                Grid3D grid(Point3D(0, 0, 0), 60, 60, 60);

                Sphere s1(Point3D(15, 15, 15), 15);
                Sphere s2(Point3D(35, 35, 35), 15);
                DoubleSphere ds(s1, s2);
                grid.setPropsValues(ds);
                grid.writeIntersect(meshesPath+"sphere.mesh");

                displayMesh(meshesPath.toStdString()+"sphere.mesh");
                break;
            }
            case 4: {
                cout << "Cylinder generation..." << endl << endl;
                Grid3D grid(Point3D(0, 0, 0), 60, 60, 60);

                NSphere ns;
                float j = 45, k = 0.01;
                for (int i = 10; i < 60; i += 1) {
                    Sphere* s = new Sphere(Point3D(i, 20, j), 8);
                    ns.addSphere(s);
                    j -= k;
                    k += 0.01;
                }
                Sphere sb1(Point3D(55, 25, 30), 10);
                Sphere sb2(Point3D(55, 15, 30), 10);
                ns.addSphere(&sb1);
                ns.addSphere(&sb2);

                Sphere s99(Point3D(25, 25, 25), 35);

                grid.setPropsValues(ns);
                grid.writeIntersect(meshesPath+"cylinder.mesh");

                displayMesh(meshesPath.toStdString()+"cylinder.mesh");
                break;
            }
            case 99: {
                cout << "Exiting..." << endl << endl;
                break;
            }
            default: {
                cout << "Invalid choice." << endl << endl;
            }
        }
    }

    return 0;
}



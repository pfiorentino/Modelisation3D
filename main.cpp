#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "surface3d.h"

using namespace std;

Surface3D parseFile(QString meshName) {
    QString meshesPath = "/Users/paul/Google Drive/Cours/Modelisation 3D/meshes/";
    Surface3D surface = Surface3D(meshName);

    QFile inputFile(meshesPath+meshName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine().simplified();

            if (line == "Vertices") {
                int verticesCount = in.readLine().simplified().toInt();

                for (int i = 0; i < verticesCount; i++){
                    QStringList splittedLine = in.readLine().simplified().split(" ");
                    if (splittedLine.count() == 4){
                        Vertice* vertice = new Vertice(splittedLine[0].toFloat(), splittedLine[1].toFloat(), splittedLine[2].toFloat());
                        surface.addVertice(vertice);
                    } else {
                        qWarning() << "Invalid vertex format";
                    }
                }
            }

            if (line == "Triangles") {
                int trianglesCount = in.readLine().simplified().toInt();

                for (int i = 0; i < trianglesCount; i++){
                    QStringList splittedLine = in.readLine().simplified().split(" ");
                    if (splittedLine.count() == 4){
                        Triangle* triangle = new Triangle(splittedLine[0].toInt(), splittedLine[1].toInt(), splittedLine[2].toInt());
                        surface.addTriangle(triangle);
                    } else {
                        qWarning() << "Invalid triangle format";
                    }
                }
            }

            //cout << line.toStdString() << endl;
        }
        inputFile.close();
    } else {
        cout << "Can't open file" << endl;
    }

    return surface;
}

void saveSurfaceFile(Surface3D surface) {
    QString meshesPath = "/Users/paul/Google Drive/Cours/Modelisation 3D/meshes/";
    QFile outputFile(meshesPath+surface.getMeshFileName());

    if (outputFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&outputFile);
        out << "MeshVersionFormatted 1" << endl;
        out << "Dimension" << endl;
        out << "3" << endl;
        out << "Vertices" << endl;
        out << surface.getNbNodes() << endl;
        for (int i = 0; i < surface.getNbNodes(); i++) {
            out << surface.getNode(i)->toMeshString() << endl;
        }

        out << "Triangles" << endl;
        out << surface.getNbTriangles() << endl;
        for (int i = 0; i < surface.getNbTriangles(); i++) {
            out << surface.getTriangle(i)->toMeshString() << endl;
        }

        out << "End" << endl;
        out.flush();
        outputFile.close();
    }
}

int main(int argc, char *argv[])
{
    qDebug() << "\x1B[2J\x1B[H";

    Surface3D surface = parseFile("bunny.mesh");
    cout << "Node 1 Normal:" << endl << surface.computeNodeNormal(1).toString().toStdString() << endl << endl;
    int random = rand() % surface.getNbNodes() + 1;
    cout << "Node random (" << random << ") Normal:" << endl << surface.computeNodeNormal(random).toString().toStdString() << endl << endl;

    cout << "Min:" << endl << surface.getMin().toString().toStdString() << endl << endl;
    cout << "Max:" << endl << surface.getMax().toString().toStdString() << endl << endl;

    cout << "Generating resized surface..." << endl;
    Surface3D resizedSurface = surface.resize(-0.01);
    saveSurfaceFile(resizedSurface);

    string command = "\"/Users/paul/Google Drive/Cours/Modelisation 3D/medit-osx\" \"/Users/paul/Google Drive/Cours/Modelisation 3D/meshes/"+QString(resizedSurface.getMeshFileName()).toStdString()+"\"";
    system(command.c_str());

    return 0;
}



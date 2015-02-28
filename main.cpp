#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


/**
 * TODO next:
 * 1) use shaders
 * 2) use shaders with normal vector as color
 * 3) delete the ViewSimpleMesh
 * 4) create a container and widget for all models
 * 5) open .obj file and show it
 */

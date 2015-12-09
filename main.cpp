#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
use element buffer
fix camera movment
    more zoom out
    when zoomed in, rotate faster
    faster rotation
    cancel camera change dir option

*/

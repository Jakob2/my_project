#include "mainwindow.h"
#include <QApplication>
#include "world.h"

int main(int argc, char *argv[])
{
    World world;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

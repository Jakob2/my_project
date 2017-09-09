#include "mainwindow.h"
#include <QApplication>
#include "world.h"
#include "db.h"

int main(int argc, char *argv[])
{
    Db::initDb();
    World world;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

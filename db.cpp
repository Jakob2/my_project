#include "db.h"

QString Db::database;
QString Db::mapTable;
QString Db::constructsTable;
QString Db::tilesTable;
QString Db::iconsTable;

/*Db::Db(){

}*/

void Db::initDb(){
    Db::database = "map";
    Db::mapTable = "map";
    Db::constructsTable = "polysd3";
    Db::tilesTable = "tiles";
    Db::iconsTable = "icon";
    connectDatabase();
}

void Db::connectDatabase(){
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/home/ok/jakob/QT4/DATABASES/"+Db::database);
    if(!m_db.open()) std::cout<< "Error: connection with database fail"<<std::endl;
    else std::cout<< "Database: connection ok"<<std::endl;
}



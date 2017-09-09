#ifndef DB_H
#define DB_H

#include "general.h"

class Db
{
public:
    //Db();

    static void initDb();
    static void connectDatabase();
    /*static QString database = "map";
    static QString mapTable = "map";
    static QString constructsTable = "polysd3";
    static QString tilesTable = "tiles";
    static QString iconsTable = "icon";*/
    static QString database;
    static QString mapTable;
    static QString constructsTable;
    static QString tilesTable;
    static QString iconsTable;
};

#endif // DB_H

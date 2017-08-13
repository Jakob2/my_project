#ifndef DB_H
#define DB_H

#include "general.h"

class Db
{
public:
    Db();

    void connectDatabase();
    QString database = "map";
    QString mapTable = "map";
    QString constructsTable = "polysd3";
    QString tilesTable = "tiles";
};

#endif // DB_H

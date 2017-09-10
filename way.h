#ifndef WAY_H
#define WAY_H

#include "general.h"
#include "world.h"
#include "db.h"
#include "vector.h"

class Way
{
public:
    Way();

    struct wayStruct{
        float x = .0;
        float z = .0;
        bool active = false;
        bool build = false;
        bool init = true;
        QString baseX = 0;
        QString baseZ = 0;
        std::vector<QString> spanX;
        std::vector<QString> spanZ;
    }waystuff;

    void selectWay();
    void insertWay(QString map, std::vector<std::vector<std::vector<float>>> &way, QString x, QString z, QString turn);
    //void insertWay(QString map, std::vector<std::vector<std::vector<float>>> &way, QString xz);

    void drawWay(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles);
    void calcAngle();

    int baseX, baseZ;
    std::vector<int> spanX;
    std::vector<int> spanZ;
    static std::vector<std::vector<std::vector<float>>> way;

private:
    void setWay(int size);
    void colorway(int x, int z);
    float angle;
    void waySouth(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int xx, int zz);
    void wayWest(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int xx, int zz);
    void wayNorth(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int xx, int zz);
    void wayEast(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int xx, int zz);

    void drawStraight(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int angle, int flag);
    //void drawStraightZ(vector<vector<vector<float>>> &way, int x, int z);
    void straightWay(std::vector<std::vector<std::vector<float>>> &way, std::vector<std::vector<std::vector<int>>> &mapTiles, int x, int z, int xx, int zz);

    void setWaySpanX(int bZ, int sX, int sXX);
    void setWaySpanZ(int bX, int sZ, int sZZ);

    QString id();

};

#endif // WAY_H

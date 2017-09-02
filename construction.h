#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include "general.h"
#include "world.h"
#include "db.h"
#include "shape.h"

class Construction : public Db, public Shape
{
public:
    Construction();
    static std::vector<std::vector<std::vector<float>>> construct;
    void setConstruct(int size);
    void selectConstructs(QString map);
    void insertConstruct(QString map, QString name);

    void constructs(std::vector<std::vector<std::vector<float>>> &construct, float xPos, float zPos);
    std::vector<std::vector<std::vector<float>>> token;
    void initToken(int size);
    void createToken(QString constructId);
    //void setToken(int i, std::vector<std::vector<std::vector<float>>> &construct);
    void wireToken(std::vector<std::vector<std::vector<float>>> token, int x, int z, float offX, float offZ, std::vector<std::vector<std::vector<int>>> &mapTiles);


private:
    int tIndex = 0;
    const float clip = 0.5;

    QString id();
    //int tIndex = 0;
};

#endif // CONSTRUCTION_H

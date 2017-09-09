#ifndef FIELD_H
#define FIELD_H

#include "general.h"
#include "world.h"
#include "db.h"
#include "shape.h"

class Field// : public Db//, private Shape
{
public:
    Field();

    struct fieldstruct{
        float areaX = .0;
        float areaZ = .0;
        bool activate = false;
        bool build = false;
        bool init = true;
    }fieldstuff;

    //void selectFieldSet();
    void selectField(QString name);
    void insertFieldPart(QString map, QString name, std::vector<std::vector<std::vector<float>>> &field, int xLow, int xHigh, int zLow, int zHigh);
    void fieldarea(std::vector<std::vector<std::vector<float>>> &field, float xPos, float zPos);

    static std::vector<int> fieldSet;
    static std::vector<std::vector<std::vector<float>>> field;

private:
    void setField(int size);
    void southarea(std::vector<std::vector<std::vector<float>>> &field, int f, float xPos, float zPos);
    void westarea(std::vector<std::vector<std::vector<float>>> &field, int f, float xPos, float zPos);
    void northarea(std::vector<std::vector<std::vector<float>>> &field, int f, float xPos, float zPos);
    void eastarea(std::vector<std::vector<std::vector<float>>> &field, int f, float xPos, float zPos);

    void fieldSQL(QString map, QString name, std::vector<std::vector<std::vector<float>>> &field, int x, int z);
    int fieldValidation(int x, int z);

    QString id();
};

#endif // FIELD_H

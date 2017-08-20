#ifndef ICON_H
#define ICON_H

#include "general.h"
#include "world.h"
#include "db.h"
#include "menumetrics.h"

class Icon : public Db, protected MenuMetrics
{
public:
    Icon();
    std::vector<std::vector<int>> icons;
    void selectIcons();
    void drawIcon();

private:
    void setIcons();
    int numIcons = 4;
    //std::vector<float> iconPos = {.76,.79, .861,.79, .76,.59, .861,.59};
};

#endif // ICON_H

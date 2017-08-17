#ifndef ZOOM_H
#define ZOOM_H

#include "general.h"
#include "world.h"

class Zoom
{
public:
    Zoom();
    void zoomIn();
    void zoomOut();

private:
    void plus();
    void minus();
};

#endif // ZOOM_H

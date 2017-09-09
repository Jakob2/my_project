#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "general.h"
#include "world.h"
#include "tilemap.h"
//#include "menu.h"
#include "mouseray.h"
#include "gui.h"
//#include "construction.h"

class GlWidget : public QGLWidget, public Tilemap, public Mouseray, public Gui //, public Construction, public Menu
{
public:
    explicit GlWidget(QWidget * parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Tilemap tilemap;
    QTimer timer;
    int pressWinX, pressWinY, moveWinX, moveWinY;

    void ddd();
    void dd();

    void setIntersection(int mouseX, int mouseY);
    std::vector<float> setIntersectionTest(int mouseX, int mouseY);
    bool onTilemap(int mouseX, int mouseY);
    void drawUniqueColoredGui(int x, int y);

    void createToken(QMouseEvent *event);
    void buildAHouse();
    void crackHouse();
};

#endif // GLWIDGET_H

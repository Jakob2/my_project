#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "general.h"
#include "world.h"
#include "tilemap.h"
#include "menu.h"

class GlWidget : public QGLWidget, public Tilemap, public Menu
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
    QTimer timer;
    int pressWinX, pressWinY, moveWinX, moveWinY;
    std::vector<int> move = {1,1};

    void ddd();
    void dd();
};

#endif // GLWIDGET_H

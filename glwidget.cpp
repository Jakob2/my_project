#include "glwidget.h"

GlWidget::GlWidget(QWidget * parent) : QGLWidget(parent){
    setFocusPolicy(Qt::StrongFocus);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
    calcCameraMoveUnits();
}

void GlWidget::initializeGL(){
    glClearColor(0.5, 0.5, 0.5, 1);
    glEnable(GL_DEPTH_TEST);
    setMouseTracking(true);
}

void GlWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    resizeGL(0,0);
    ddd();
    glScalef(World::zoom, World::zoom, World::zoom);
    ground(World::x, World::z, Tilemap::mapTiles);
    /*constructs(Db::construct, X, Z);*/

    dd();
    drawMenu();

    ddd();
    glScalef(World::zoom, World::zoom, World::zoom);
    ground(World::x, World::z, Tilemap::mapTiles);
    crossfade();
}

void GlWidget::resizeGL(int w, int h){
    World::height = GlWidget::height();
    World::width = GlWidget::width();
}

void GlWidget::ddd(){
    glViewport(0, 0, World::width, World::height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)World::width/World::height, 0.01, 100.0);
    gluLookAt(World::eyeX,World::eyeY,World::eyeZ, 0,0,0, 0,1,0);
}

void GlWidget::dd(){
    glViewport(0, 0, World::width, World::height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1,0,1);
}

void GlWidget::setIntersection(){
    glClear(GL_DEPTH_BUFFER_BIT);
    ground(World::x, World::z, Tilemap::mapTiles);
    calculateGLCoords(pressWinX, pressWinY);
}

void GlWidget::keyPressEvent(QKeyEvent *event){
    calcCameraMoveUnits();
    switch(event->key()){
    case Qt::Key_A:
        World::x += camMoveUnit[0];
        World::z -= camMoveUnit[1];
        break;
    case Qt::Key_D:
        World::x -= camMoveUnit[0];
        World::z += camMoveUnit[1];
        break;
    case Qt::Key_W:
        World::x += camMoveUnit[1];
        World::z += camMoveUnit[0];
        break;
    case Qt::Key_S:
        World::x -= camMoveUnit[1];
        World::z -= camMoveUnit[0];
        break;
    }
    paintGL();
}

void GlWidget::mousePressEvent(QMouseEvent *event){
    World::mousePressed = true;
    pressWinX = event->pos().x();
    pressWinY = event->pos().y();
    if(panelCompass(mouseToMenuGrid(moveWinX,moveWinY))) turnCamera(mouseToMenuGrid(moveWinX,moveWinY));
    if(panelWorld(mouseToMenuGrid(moveWinX,moveWinY))) setIntersection();
}

void GlWidget::mouseReleaseEvent(QMouseEvent *event){
    World::mousePressed = false;
}

void GlWidget::mouseMoveEvent(QMouseEvent *event){
    moveWinX = event->pos().x();
    moveWinY = event->pos().y();
    if(World::mousePressed && panelCompass(mouseToMenuGrid(moveWinX,moveWinY))) turnCamera(mouseToMenuGrid(moveWinX,moveWinY));
}

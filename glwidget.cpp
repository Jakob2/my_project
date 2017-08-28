#include "glwidget.h"

GlWidget::GlWidget(QWidget * parent) : QGLWidget(parent){
    setFocusPolicy(Qt::StrongFocus);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
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
    /*constructs(Construction::construct, World::x, World::z);
    if(World::moveConstruct && inRange()){
        wireToken(token, World::tile[2], World::tile[3], World::x, World::z, Tilemap::mapTiles);
    }*/
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
    unsunkenGround(World::x, World::z, Tilemap::mapTiles);
    calculateGLCoords(pressWinX,pressWinY);
    glClear(GL_DEPTH_BUFFER_BIT);
}

bool GlWidget::onTilemap(){
    glClear(GL_DEPTH_BUFFER_BIT);
    unsunkenGround(World::x, World::z, Tilemap::mapTiles);
    return checkIfOnTilemap(pressWinX, pressWinY);
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
    std::cout<<"PRESSWIN: "<<pressWinX<<"-"<<pressWinY<<std::endl;
    if(panelCompass(mouseToMenuGrid(pressWinX,pressWinY))) turnCamera(mouseToMenuGrid(pressWinX,pressWinY));
    if(panelWorld(mouseToMenuGrid(pressWinX,pressWinY)) && onTilemap()) setIntersection();
    if(panelZoom(mouseToMenuGrid(pressWinX,pressWinY))) zoom();

    //glClear(GL_DEPTH_BUFFER_BIT);

    /*if(panelBuildings(mouseToMenuGrid(moveWinX,moveWinY))){
        onBuildings(event);
        //insertConstruct(QString::number(1), QString::number(World::buildingOption));
        //selectConstructs(QString::number(1));
    }*/
}

void GlWidget::mouseReleaseEvent(QMouseEvent *event){
    World::mousePressed = false;
}

void GlWidget::mouseMoveEvent(QMouseEvent *event){
    moveWinX = event->pos().x();
    moveWinY = event->pos().y();
    if(World::mousePressed && panelCompass(mouseToMenuGrid(moveWinX,moveWinY))) turnCamera(mouseToMenuGrid(moveWinX,moveWinY));
    if(panelBuildings(mouseToMenuGrid(moveWinX,moveWinY))) hoverBuildings(mouseToMenuGrid(moveWinX,moveWinY));
    if(panelZoom(mouseToMenuGrid(moveWinX,moveWinY))) hoverZoom(mouseToMenuGrid(moveWinX,moveWinY));
    if(panelCompass(mouseToMenuGrid(moveWinX,moveWinY))) hoverCompass(mouseToMenuGrid(moveWinX,moveWinY));
    //if(!panelMenu(moveWinX,moveWinY)) calculateGLCoords(moveWinX,moveWinY);

}

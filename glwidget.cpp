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


    dd();
    drawMenu();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //uniqueColoredOptions();

    //glClear(GL_DEPTH_BUFFER_BIT);
    ddd();
    glScalef(World::zoom, World::zoom, World::zoom);
    ground(World::x, World::z, Tilemap::mapTiles);
    crossfade();
    constructs(Construction::construct, World::x, World::z);
    if(World::token){
        wireToken(token, World::tile[4], World::tile[5], World::x, World::z, Tilemap::mapTiles);
    }

    /*glClear(GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ddd();
    unsunkenGround(World::x, World::z, Tilemap::mapTiles);
    dd();
    uniqueColoredOptions();*/

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

void GlWidget::setIntersection(int mouseX, int mouseY){
    glClear(GL_DEPTH_BUFFER_BIT);
    unsunkenGround(World::x, World::z, Tilemap::mapTiles);
    calculateGLCoords(mouseX,mouseY);
    glClear(GL_DEPTH_BUFFER_BIT);
}

bool GlWidget::onTilemap(int mouseX, int mouseY){
    glClear(GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    dd();
    uniqueColoredOptions();
    ddd();
    glScalef(World::zoom, World::zoom, World::zoom);
    unsunkenGround(World::x, World::z, Tilemap::mapTiles);
    /*glClear(GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    dd();
    uniqueColoredOptions();
    ddd();
    unsunkenGround(World::x, World::z, Tilemap::mapTiles);*/
    return checkIfOnTilemap(mouseX, mouseY);
}

void GlWidget::drawUniqueColoredGui(int x, int y){
    dd();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    uniqueColoredOptions();
    uniqueColoredPlus();
    uniqueColoredMinus();
    uniqueColoredCompass();
    readPixelColor(x,y);
    hoverGui(x,y);
}

void GlWidget::createToken(QMouseEvent *event){
    panelBuildings(event);
    selectToken(QString::number(World::buildingOption));
    World::token ? World::token = false : World::token = true;
    if(World::token) std::cout<<"TRUE TOKEN"<<std::endl;
    else std::cout<<"FALSE TOKEN"<<std::endl;
}

void GlWidget::buildAHouse(){
    insertConstruct(QString::number(World::map), QString::number(World::buildingOption),QString::number(World::tile[4]+1),QString::number(World::tile[5]+1));
    updateTilesOpen(QString::number(World::tile[4]), QString::number(World::tile[5]));
    selectConstructs(QString::number(1));
    selectMapTiles();
    World::token = false;
}

void GlWidget::crackHouse(){
    deleteConstruct(QString::number(World::constructId));
    selectConstructs(QString::number(World::map));
    updateOpen(QString::number(World::tile[4]), QString::number(World::tile[5]), QString::number(1));
    selectMapTiles();
    World::token = false;
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
    //std::cout<<"PRESSWIN: "<<pressWinX<<"-"<<pressWinY<<std::endl;
    if(World::hoverCompass == 1 && onMenu(moveWinX)) turnCamera(mouseToMenuGrid(pressWinX,pressWinY));
    if(panelWorld(mouseToMenuGrid(pressWinX,pressWinY)) && onTilemap(pressWinX,pressWinY)) setIntersection(pressWinX,pressWinY);
    if(World::hoverZoom == 0 || World::hoverZoom == 1) zoom();
    if(onMenu(pressWinX) && World::hoverBuilding != -1 && World::hoverBuilding != 999) createToken(event);
    if(onMenu(pressWinX) && World::buildingOption == 999) crackHouse();
    if(onTilemap(pressWinX,pressWinY) && World::token && World::validPlace) buildAHouse();
}

void GlWidget::mouseReleaseEvent(QMouseEvent *event){
    World::mousePressed = false;
}

void GlWidget::mouseMoveEvent(QMouseEvent *event){
    moveWinX = event->pos().x();
    moveWinY = event->pos().y();
    if(World::hoverCompass == 1 && World::mousePressed) turnCamera(mouseToMenuGrid(moveWinX,moveWinY));
    if(onMenu(moveWinX)) drawUniqueColoredGui(moveWinX,moveWinY);
    if(World::token){
        if(onTilemap(moveWinX,moveWinY)){
            setIntersection(moveWinX,moveWinY);
        }
    }
}

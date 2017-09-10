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
    //Db::initDb();
}

void GlWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    resizeGL(0,0);
    dd();
    drawMenu();
    ddd();
    glScalef(World::view.zoom, World::view.zoom, World::view.zoom);
    ground(World::x, World::z, Tilemap::mapTiles);
    crossfade();
    constructs(Construction::construct, World::x, World::z);
    if(World::token) wireToken(token, World::tile[4], World::tile[5], World::x, World::z, Tilemap::mapTiles);
    if(fieldstuff.build) fieldarea(Field::field, World::x,World::z);
    if(waystuff.build) drawWay(Way::way, Tilemap::mapTiles);
}

void GlWidget::resizeGL(int w, int h){
    World::view.height = GlWidget::height();
    World::view.width = GlWidget::width();
}

void GlWidget::ddd(){
    glViewport(0,0, World::view.width,World::view.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)World::view.width/World::view.height, 0.01, 100.0);
    gluLookAt(World::view.eyeX,World::view.eyeY,World::view.eyeZ, 0,0,0, 0,1,0);
}

void GlWidget::dd(){
    glViewport(0,0, World::view.width,World::view.height);
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

std::vector<float> GlWidget::setIntersectionTest(int mouseX, int mouseY){
    glClear(GL_DEPTH_BUFFER_BIT);
    unsunkenGround(World::x, World::z, Tilemap::mapTiles);
    std::vector<float> out;
    out = calculateGLCoordsTest(mouseX,mouseY);
    glClear(GL_DEPTH_BUFFER_BIT);
    return out;
}

bool GlWidget::onTilemap(int mouseX, int mouseY){
    glClear(GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    dd();
    uniqueColoredOptions();
    uniqueColoredCompass();
    uniqueColoredZoom();
    ddd();
    glScalef(World::view.zoom, World::view.zoom, World::view.zoom);
    unsunkenGround(World::x, World::z, Tilemap::mapTiles);
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
    World::buildingOption = -1;
    std::cout<<"CRACK ID: "<<World::buildingOption<<std::endl;
}

void GlWidget::activateField(){
    selectField(QString::number(6));
    fieldstuff.activate ? fieldstuff.activate = false : fieldstuff.activate = true;
    fieldstuff.build = false;
    fieldstuff.init = true;
}

void GlWidget::plantField(){
    if(fieldstuff.activate){
        fieldstuff.build ? fieldstuff.build = false : fieldstuff.build = true;
        if(fieldstuff.init){
            testIntersection = setIntersectionTest(pressWinX,pressWinY);
            fieldstuff.areaX = testIntersection[0];
            fieldstuff.areaZ  = testIntersection[2];
        }
        fieldstuff.init = false;
        if(!fieldstuff.build){
            std::cout<<"PLANT THE FIELD"<<std::endl;
            insertFieldPart(QString::number(World::map), QString::number(6), Field::field, ceil(fieldstuff.areaX-World::x),ceil(World::tile[2]-World::x), ceil(fieldstuff.areaZ-World::z),ceil(World::tile[3]-World::z));
            selectConstructs(QString::number(World::map));
            selectMapTiles();
            fieldstuff.init = true;
        }
    }
}

void GlWidget::activateWay(){

}

void GlWidget::buildWay()
{

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
    case Qt::Key_Escape:
        World::constructId = -1;
        break;
    }
    //std::cout<<"AREA_X: "<<World::areaX<<" - AREA_Z: "<<World::areaZ<<std::endl;
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
    //plant a field
    if(onMenu(pressWinX) && World::hoverBuilding == 4) activateField();
    if(onTilemap(pressWinX,pressWinY) && World::buildingOption == 6) plantField();
    //build a way
    if(onMenu(pressWinX) && World::hoverBuilding == 3){
        selectWay();
        waystuff.active ? waystuff.active = false : waystuff.active = true;
        waystuff.build = false;
        waystuff.init = true;
    }
    if(onTilemap(moveWinX,moveWinY) && World::buildingOption == 7){
        if(waystuff.active){
            waystuff.build ? waystuff.build = false : waystuff.build = true;
            if(waystuff.init && onTilemap(moveWinX,moveWinY)){
                testIntersection = setIntersectionTest(pressWinX,pressWinY);
                waystuff.x = ceil(testIntersection[0]-World::x)-1;
                waystuff.z = ceil(testIntersection[2]-World::z)-1;
            }
            waystuff.init = false;
            if(!waystuff.build){
                std::cout<<"BUILD THE WAY"<<std::endl;
                for(auto i : waystuff.spanZ) std::cout<<"way x: "<<i.toStdString()<<std::endl;
                for(int x=0; x<(int)waystuff.spanX.size(); x++){
                    insertWay(QString::number(World::map), Way::way, waystuff.spanX[x],waystuff.baseZ, QString::number(90));
                }
                for(int z=0; z<(int)waystuff.spanZ.size(); z++){
                    insertWay(QString::number(World::map), Way::way, waystuff.baseX, waystuff.spanZ[z], QString::number(0));
                }
                selectConstructs(QString::number(World::map));
                selectMapTiles();
                waystuff.init = true;
            }
        }
    }
    //build a house
    if(onMenu(pressWinX) && World::hoverBuilding != -1 && World::hoverBuilding != 999) createToken(event);
    if(onMenu(pressWinX) && World::buildingOption == 999) crackHouse();
    if(onTilemap(pressWinX,pressWinY) && World::token && World::validPlace && World::buildingOption != 6 && World::buildingOption != 7) buildAHouse();

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

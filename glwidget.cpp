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
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //uniqueColoredOptions();

    //glClear(GL_DEPTH_BUFFER_BIT);
    ddd();
    glScalef(World::zoom, World::zoom, World::zoom);
    ground(World::x, World::z, Tilemap::mapTiles);
    crossfade();
    constructs(Construction::construct, World::x, World::z);
    if(World::token){ // && onTilemap(moveWinX,moveWinY)
        wireToken(token, World::tile[4], World::tile[5], World::x, World::z, Tilemap::mapTiles);
    }
    if(World::field[1]){
        fieldarea(Field::field, World::x,World::z);
    }
    //if(World::way[3]){
    if(waystuff.build){
        drawWay(Way::way, Tilemap::mapTiles);
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
    glViewport(0,0, World::width,World::height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)World::width/World::height, 0.01, 100.0);
    gluLookAt(World::eyeX,World::eyeY,World::eyeZ, 0,0,0, 0,1,0);
}

void GlWidget::dd(){
    glViewport(0,0, World::width,World::height);
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
    //paintGL();
    return out;
}

bool GlWidget::onTilemap(int mouseX, int mouseY){
    glClear(GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    dd();
    uniqueColoredOptions();
    uniqueColoredCompass();
    uniqueColoredZoom();
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
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    std::cout<<"CRACK ID: "<<World::buildingOption<<std::endl;
}

void GlWidget::activateField(){
    selectField(QString::number(6));
    World::field[0] ? World::field[0] = false : World::field[0] = true;
    World::field[1] = false;
    World::field[2] = true;
    if(World::field[0]) std::cout<<"START THE FIELD 0"<<std::endl;
    else std::cout<<"END THE FIELD 0"<<std::endl;
}

void GlWidget::plantField(){
    if(World::field[0]){

        World::field[1] ? World::field[1] = false : World::field[1] = true;

        if(World::field[1]) std::cout<<"START THE FIELD 1"<<std::endl;
        else std::cout<<"END THE FIELD 1"<<std::endl;

        if(World::field[2]){
            //calculateGLCoords(pressWinX,pressWinY);
            testIntersection = setIntersectionTest(pressWinX,pressWinY);
            //testIntersection = calculateGLCoordsTest(pressWinX,pressWinY);
            World::areaX = testIntersection[0];
            World::areaZ = testIntersection[2];
        }
        World::field[2] = false;

        if(!World::field[1]){
            std::cout<<"PLANT THE DAMN FIELD"<<std::endl;
            insertFieldPart(QString::number(World::map), QString::number(6), Field::field, ceil(World::areaX-World::x),ceil(World::tile[2]-World::x), ceil(World::areaZ-World::z),ceil(World::tile[3]-World::z));
            //insertFieldPart(QString::number(World::map), QString::number(6), Field::field, ceil(World::areaX),ceil(World::tile[2]), ceil(World::areaZ),ceil(World::tile[3]));
            //std::cout<<"AREAX: "<<floor(World::areaX)<<" - AREAZ: "<<floor(World::areaZ)<<" // TILEX: "<<ceil(World::tile[2])<<" - TILEZ: "<<ceil(World::tile[3])<<std::endl;
            selectConstructs(QString::number(World::map));
            selectMapTiles();
            World::field[1] = false;
            World::field[2] = true;
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
    std::cout<<"AREA_X: "<<World::areaX<<" - AREA_Z: "<<World::areaZ<<std::endl;
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
        /*World::way[2] ? World::way[2] = 0 : World::way[2] = 1;
        World::way[3] = false;
        World::way[4] = true;*/
        waystuff.active ? waystuff.active = false : waystuff.active = true;
        waystuff.build = false;
        waystuff.init = true;
        /*if(World::way[2]) std::cout<<"START THE WAY 2(activate)"<<std::endl;
        else std::cout<<"END THE WAY 2(activate)"<<std::endl;*/
    }
    if(onTilemap(moveWinX,moveWinY) && World::buildingOption == 7){
        //if(World::way[2]){
        if(waystuff.active){
            //World::way[3] ? World::way[3] = 0 : World::way[3] = 1;
            waystuff.build ? waystuff.build = false : waystuff.build = true;

            /*if(World::way[3]) std::cout<<"START THE WAY 3"<<std::endl;
            else std::cout<<"END THE WAY 3"<<std::endl;*/

            //if(World::way[4] && onTilemap(moveWinX,moveWinY)){
            if(waystuff.init && onTilemap(moveWinX,moveWinY)){
                testIntersection = setIntersectionTest(pressWinX,pressWinY);
                /*World::way[0] = ceil(testIntersection[0]-World::x);
                World::way[1] = ceil(testIntersection[2]-World::z);*/
                waystuff.x = ceil(testIntersection[0]-World::x)-1;
                waystuff.z = ceil(testIntersection[2]-World::z)-1;
            }
            //World::way[4] = false;
            waystuff.init = false;

            //if(!World::way[3]){
            if(!waystuff.build){
                std::cout<<"BUILD THE DAMN WAY"<<std::endl;
                /*World::way[3] = false;
                World::way[4] = true;*/
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

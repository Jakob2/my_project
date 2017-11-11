#include "glwidget.h"

GlWidget::GlWidget(QWidget * parent) : QGLWidget(parent){
    setFocusPolicy(Qt::StrongFocus);
    connect(&timer, SIGNAL(timeout()), this, SLOT(paintGL()));
    timer.start(16);
}

void GlWidget::initializeGL(){
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glShadeModel(GL_FLAT);
    glClearColor(0.5, 0.5, 0.5, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    setMouseTracking(true);
    //Db::initDb();
}

void GlWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    resizeGL(0,0);
    dd();
    drawMenu();
    //drawUniqueColoredGui(0,0);
    ddd();
    glScalef(World::view.zoom, World::view.zoom, World::view.zoom);
    ground(World::map.x, World::map.z, Tilemap::mapTiles);
    //ground(0, 0, Tilemap::mapTiles);

    crossfade();

    constructs(Construction::construct, World::map.x, World::map.z);
    //constructs(Construction::construct, 0, 0);


    if(World::map.token) wireToken(token, World::map.tile[4], World::map.tile[5], World::map.x, World::map.z, Tilemap::mapTiles);
    if(fieldstuff.build) fieldarea(Field::field, World::map.x,World::map.z);
    if(waystuff.build && World::map.token) drawWay(Way::way, Tilemap::mapTiles);

    //dd();
    //drawMenu();
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
    //gluLookAt(World::view.eyeX+World::map.x,World::view.eyeY,World::view.eyeZ+World::map.z, 0+World::map.x,0,0+World::map.z, 0,1,0);
    lightsOn();
}

void GlWidget::dd(){
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glViewport(0,0, World::view.width,World::view.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1,0,1);
}

void GlWidget::setIntersection(int mouseX, int mouseY){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    unsunkenGround(World::map.x, World::map.z);//, Tilemap::mapTiles);
    calculateGLCoords(mouseX,mouseY);
    //glClear(GL_DEPTH_BUFFER_BIT);
    //paintGL();
    updateGL();
}

std::vector<float> GlWidget::setIntersectionTest(int mouseX, int mouseY){
    glClear(GL_DEPTH_BUFFER_BIT);
    unsunkenGround(World::map.x, World::map.z);//, Tilemap::mapTiles);
    std::vector<float> out;
    out = calculateGLCoordsTest(mouseX,mouseY);
    glClear(GL_DEPTH_BUFFER_BIT);
    paintGL();
    return out;
}

/*bool GlWidget::onTilemap(int mouseX, int mouseY){
    glClear(GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //dd();
    /*uniqueColoredOptions();
    uniqueColoredCompass();
    uniqueColoredZoom();
    ddd();
    glScalef(World::view.zoom, World::view.zoom, World::view.zoom);
    unsunkenGround(World::map.x, World::map.z);//, Tilemap::mapTiles);
    //readPixelColor(pressWinX,pressWinY);
    //return checkIfOnTilemap(mouseX, mouseY);
    return checkIfOnTilemap();
}*/

void GlWidget::drawUniqueColoredGui(int x, int y){
    dd();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    uniqueColoredOptions();
    uniqueColoredPlus();
    uniqueColoredMinus();
    uniqueColoredCompass();
    readPixelColor(x,y);
    hoverGui();
    //paintGL();
    updateGL();
}

void GlWidget::createToken(QMouseEvent *event){
    panelBuildings(event);
    selectToken(QString::number(World::gui.buildingOption));
    World::map.token ? World::map.token = false : World::map.token = true;
    if(World::map.token) std::cout<<"TRUE TOKEN"<<std::endl;
    else std::cout<<"FALSE TOKEN"<<std::endl;

    waystuff.active = false;
    waystuff.build = false;
    waystuff.init = true;

    fieldstuff.activate = false;
    fieldstuff.build = false;
    fieldstuff.init = true;
}

void GlWidget::buildAHouse(){
    insertConstruct(QString::number(World::map.map), QString::number(World::gui.buildingOption),QString::number(World::map.tile[4]+1),QString::number(World::map.tile[5]+1));
    updateTilesOpen(QString::number(World::map.tile[4]), QString::number(World::map.tile[5]));
    selectConstructs(QString::number(1));
    selectMapTiles();
    World::map.token = false;
}

void GlWidget::crackHouse(){
    deleteConstruct(QString::number(World::map.constructId));
    selectConstructs(QString::number(World::map.map));
    updateOpen(QString::number(World::map.tile[4]), QString::number(World::map.tile[5]), QString::number(1));
    selectMapTiles();
    World::map.token = false;
    World::gui.buildingOption = -1;
    std::cout<<"CRACK ID: "<<World::gui.buildingOption<<std::endl;
}

void GlWidget::activateField(){
    selectField(QString::number(6));
    fieldstuff.activate ? fieldstuff.activate = false : fieldstuff.activate = true;
    fieldstuff.build = false;
    fieldstuff.init = true;
    World::gui.selected ? World::gui.selected = false : World::gui.selected = true;
}

void GlWidget::plantField(){
    //std::cout<<"PLANT FIELD FUNCTION"<<std::endl;
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
            insertFieldPart(QString::number(World::map.map), QString::number(6), Field::field, ceil(fieldstuff.areaX-World::map.x),ceil(World::map.tile[2]-World::map.x), ceil(fieldstuff.areaZ-World::map.z),ceil(World::map.tile[3]-World::map.z));
            selectConstructs(QString::number(World::map.map));
            selectMapTiles();
            fieldstuff.init = true;
        }
    }
}

void GlWidget::activateWay(){
    selectWay();
    waystuff.active ? waystuff.active = false : waystuff.active = true;
    waystuff.build = false;
    waystuff.init = true;
    World::gui.selected ? World::gui.selected = false : World::gui.selected = true;
}

void GlWidget::buildWay(){
    if(waystuff.active){
        waystuff.build ? waystuff.build = false : waystuff.build = true;
        //if(waystuff.init && onTilemap(moveWinX,moveWinY)){
        if(waystuff.init && !World::mouse.onMenu){
            testIntersection = setIntersectionTest(pressWinX,pressWinY);
            waystuff.x = ceil(testIntersection[0]-World::map.x)-1;
            waystuff.z = ceil(testIntersection[2]-World::map.z)-1;
        }
        waystuff.init = false;
        if(!waystuff.build){
            std::cout<<"BUILD THE WAY"<<std::endl;
            for(auto i : waystuff.spanZ) std::cout<<"way x: "<<i.toStdString()<<std::endl;
            for(int x=0; x<(int)waystuff.spanX.size(); x++){
                insertWay(QString::number(World::map.map), Way::way, waystuff.spanX[x],waystuff.baseZ, QString::number(90));
            }
            for(int z=0; z<(int)waystuff.spanZ.size(); z++){
                insertWay(QString::number(World::map.map), Way::way, waystuff.baseX, waystuff.spanZ[z], QString::number(0));
            }
            selectConstructs(QString::number(World::map.map));
            selectMapTiles();
            waystuff.init = true;
        }
    }
}

void GlWidget::resetGuiSelection(){
    if(!World::gui.selected){
        fieldstuff.activate = false;
        waystuff.active = false;
    }
}

void GlWidget::keyPressEvent(QKeyEvent *event){
    calcCameraMoveUnits();
    switch(event->key()){
    case Qt::Key_A:
        World::map.x += camMoveUnit[0];
        World::map.z -= camMoveUnit[1];
        break;
    case Qt::Key_D:
        World::map.x -= camMoveUnit[0];
        World::map.z += camMoveUnit[1];
        break;
    case Qt::Key_W:
        World::map.x += camMoveUnit[1];
        World::map.z += camMoveUnit[0];
        break;
    case Qt::Key_S:
        World::map.x -= camMoveUnit[1];
        World::map.z -= camMoveUnit[0];
        break;
    case Qt::Key_Escape:
        World::map.constructId = -1;
        break;
    case Qt::Key_U:
        World::light.height += 0.05;
        break;
    case Qt::Key_J:
        World::light.height -= 0.05;
        break;
    case Qt::Key_M:
        World::light.ambient += 0.05;
        break;
    case Qt::Key_N:
        World::light.ambient -= 0.05;
        break;
    case Qt::Key_B:
        World::light.diffuse += 0.05;
        break;
    case Qt::Key_V:
        World::light.diffuse -= 0.05;
        break;
    }
    //std::cout<<"ambient: "<<World::light.ambient<<" - diffuse: "<<World::light.diffuse<<" - height: "<<World::light.height<<std::endl;
    //std::cout<<"AREA_X: "<<World::areaX<<" - AREA_Z: "<<World::areaZ<<std::endl;
    updateGL();
}

void GlWidget::mousePressEvent(QMouseEvent *event){
    World::mouse.pressed = true;
    pressWinX = event->pos().x();
    pressWinY = event->pos().y();

    //onTilemap(pressWinX, pressWinY);
    drawUniqueColoredGui(pressWinX,pressWinY);

    //std::cout<<"PRESSWIN: "<<pressWinX<<"-"<<pressWinY<<std::endl;
    if(World::gui.hoverCompass == 1 && onMenu(moveWinX)) turnCamera(mouseToMenuGrid(pressWinX,pressWinY));
    //if(panelWorld(mouseToMenuGrid(pressWinX,pressWinY)) && onTilemap(pressWinX,pressWinY)) setIntersection(pressWinX,pressWinY);
    if(panelWorld(mouseToMenuGrid(pressWinX,pressWinY)) && !World::mouse.onMenu) setIntersection(pressWinX,pressWinY);
    if(World::gui.hoverZoom == 0 || World::gui.hoverZoom == 1) zoom();
    if(onMenu(pressWinX) && World::gui.hoverBuilding != -1 && World::gui.hoverBuilding != 999) createToken(event);
    //plant a field
    if(onMenu(pressWinX) && World::gui.hoverBuilding == 4) activateField();
    //if(onTilemap(pressWinX,pressWinY) && World::gui.buildingOption == 6 && World::gui.selected) plantField();
    if(!World::mouse.onMenu && World::gui.buildingOption == 6 && World::gui.selected) plantField();
    //build a way
    if(onMenu(pressWinX) && World::gui.hoverBuilding == 3) activateWay();
    //if(onTilemap(moveWinX,moveWinY) && World::gui.buildingOption == 7 && World::gui.selected) buildWay();
    if(!World::mouse.onMenu && World::gui.buildingOption == 7 && World::gui.selected) buildWay();
    //build a house
    //if(onMenu(pressWinX) && World::gui.hoverBuilding != -1 && World::gui.hoverBuilding != 999) createToken(event);
    if(onMenu(pressWinX) && World::gui.buildingOption == 999) crackHouse();
    //if(onTilemap(pressWinX,pressWinY) && World::map.token && World::map.valid && World::gui.buildingOption != 6 && World::gui.buildingOption != 7) buildAHouse();
    if(!World::mouse.onMenu && World::map.token && World::map.valid && World::gui.buildingOption != 6 && World::gui.buildingOption != 7) buildAHouse();

    resetGuiSelection();
    updateGL();
}

void GlWidget::mouseReleaseEvent(QMouseEvent *event){
    World::mouse.pressed = false;
}

void GlWidget::mouseMoveEvent(QMouseEvent *event){
    moveWinX = event->pos().x();
    moveWinY = event->pos().y();
    onMenu(moveWinX);
    if(World::gui.hoverCompass == 1 && World::mouse.pressed) turnCamera(mouseToMenuGrid(moveWinX,moveWinY));
    //if(onMenu(moveWinX)) drawUniqueColoredGui(moveWinX,moveWinY);
    if(World::map.token && !World::mouse.onMenu){
        //if(onTilemap(moveWinX,moveWinY)){
            setIntersection(moveWinX,moveWinY);
        //}
    }
    updateGL();
}

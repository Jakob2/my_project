#-------------------------------------------------
#
# Project created by QtCreator 2017-08-13T16:51:33
#
#-------------------------------------------------

QT       += core gui opengl sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3_project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    world.cpp \
    db.cpp \
    tilemap.cpp \
    shape.cpp \
    menu.cpp \
    compass.cpp \
    vector.cpp \
    mouseray.cpp \
    building.cpp \
    zoom.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    world.h \
    general.h \
    db.h \
    tilemap.h \
    shape.h \
    menu.h \
    compass.h \
    vector.h \
    mouseray.h \
    building.h \
    zoom.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU

QMAKE_CXXFLAGS += -std=c++11

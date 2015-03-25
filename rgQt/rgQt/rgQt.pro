#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T11:55:25
#
#-------------------------------------------------

QT += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rgQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
INCLUDEPATH += /home/ajbernal/dev/bat/research/rgQt/rgQt/include
INCLUDEPATH += /home/ajbernal/dev/bat/research/rgQt/rgQt/include/io

INCLUDEPATH += . d:/c++/libs/include
LIBS += -lGLEW -O3

QMAKE_CXXFLAGS += -std=c++11

FORMS    += mainwindow.ui

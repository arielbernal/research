#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T11:21:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TreeeModel
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    gl/rgglobject.h \
    gl/rgglcamera.h \
    gl/rgglheaders.h \
    gl/rggllight.h

INCLUDEPATH += C:\dev\research\external\vs\glm

FORMS    += mainwindow.ui

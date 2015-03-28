#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T12:13:00
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rgQR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    glwidget.h

INCLUDEPATH += ./include
INCLUDEPATH += ./include/io
INCLUDEPATH += C:\dev\research\external\vs\glew-1.12.0\include
INCLUDEPATH += C:\dev\research\external\vs\glm
INCLUDEPATH += .\include
INCLUDEPATH += .\include\io


#LIBS += -lGLEW -lGL -O3
LIBS += -LC:\dev\research\external\vs\glew-1.12.0\lib\Release\x64 -lglew32s
#QMAKE_CXXFLAGS += -std=c++11

FORMS    += mainwindow.ui

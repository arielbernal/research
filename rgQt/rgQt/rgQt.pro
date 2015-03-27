#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T11:55:25
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rgQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

INCLUDEPATH += /home/ajbernal/dev/bat/research/rgQt/rgQt/include
INCLUDEPATH += /home/ajbernal/dev/bat/research/rgQt/rgQt/include/io
INCLUDEPATH += C:\dev\research\external\vs\glew-1.12.0\include
INCLUDEPATH += C:\dev\research\external\vs\glm
INCLUDEPATH += C:\dev\research\rgQt\rgQt\include
INCLUDEPATH += C:\dev\research\rgQt\rgQt\include\io


#LIBS += -lGLEW -lGL -O3
LIBS += -LC:\dev\research\external\vs\glew-1.12.0\lib\Release\x64 -lglew32s
#QMAKE_CXXFLAGS += -std=c++11

FORMS    += mainwindow.ui

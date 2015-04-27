#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T13:54:30
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rgQR
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    objectinspector.cpp \
    cameraeditpanel.cpp \
    lighteditpanel.cpp \
    qformline.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    toolbox.h \
    toolitem.h \
    objectinspector.h \
    vallineedit.h \
    gl/rgglcamera.h \
    gl/rgglcuboid.h \
    gl/rgglheaders.h \
    gl/rggllight.h \
    gl/rgglobject.h \
    gl/rgglobject3d.h \
    scene.h \
    cameraeditpanel.h \
    lighteditpanel.h \
    qformline.h \
    glwidget.h


win32 {
  INCLUDEPATH += C:\dev\research\external\vs\glew-1.12.0\include
  INCLUDEPATH += C:\dev\research\external\vs\glm
  LIBS += -LC:\dev\research\external\vs\glew-1.12.0\lib\Release\x64 -lglew32s
} else {
  LIBS += -lGLEW -lGL
}


FORMS    += mainwindow.ui

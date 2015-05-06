#-------------------------------------------------
#
# Project created by QtCreator 2015-04-23T10:23:16
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = rgOCVSerial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    glwidget.cpp \
    glprimitives.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    glwidget.h \
    robot.h \
    glprimitivies.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

CONFIG += c++11


win32 {
  INCLUDEPATH += C:\dev\research\external\vs\glew-1.12.0\include
  INCLUDEPATH += C:\dev\research\external\vs\glm
  LIBS += -LC:\dev\research\external\vs\glew-1.12.0\lib\Release\x64 -lglew32s
} else {
  LIBS += -lGLEW -lGL -lGLU
  INCLUDEPATH += -I/usr/local/include/opencv
  LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
}


RESOURCES += \
    icons.qrc

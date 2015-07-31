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
    ../common/ocvTools/imageglwidget.cpp \
    ../common/ocvTools/imagedialog.cpp \
    ../common/oglTools/glprimitives.cpp \
    detect.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    ../common/ocvTools/imageshow.h \
    ../common/ocvTools/imagedialog.h \
    ../common/ocvTools/imageglwidget.h \
    ../common/oglTools/glprimitivies.h \
    ../common/oglTools/fps.h \
    detect.h \

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    ../common/imagedialog.ui

DEPENDPATH *= $
DEPENDPATH += ../common

CONFIG += c++11

win32 {
  INCLUDEPATH += C:\dev\research\external\vs\glew-1.12.0\include
  INCLUDEPATH += C:\dev\research\external\vs\glm
  INCLUDEPATH += E:\opencv\build\include
  LIBS += -LC:\dev\research\external\vs\glew-1.12.0\lib\Release\x64 -lglew32s
  LIBS += -L"E:\opencv\build\x64\vc12\lib" -lopencv_ts300 -lopencv_world300
} else {
  LIBS += -lGLEW -lGL -lGLU
  INCLUDEPATH += -I/usr/local/include/opencv
  LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio
}


RESOURCES += \
    icons.qrc

DISTFILES +=

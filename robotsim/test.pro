#-------------------------------------------------
#
# Project created by QtCreator 2015-08-13T21:29:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    include/lodepng.cpp

HEADERS += \
    include/arg.hpp \
    include/glheaders.h \
    include/glprimitives.h \
    include/glservo.h \
    include/lodepng.h \
    include/scoped_timer.h \
    include/scoped_timer.impl \
    include/svector.h

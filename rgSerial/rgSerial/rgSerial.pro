#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T16:13:58
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET = enumerator
TEMPLATE = app

SOURCES += \
    main.cpp

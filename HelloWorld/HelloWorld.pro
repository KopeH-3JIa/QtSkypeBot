#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T05:10:14
#
#-------------------------------------------------
CONFIG += console
QT -= gui widgets
QT += axcontainer
LIBS += -L../Action/release/ -lAction
TARGET = HelloWorld
TEMPLATE = lib
DEFINES += HELLOWORLD_LIBRARY

SOURCES += helloworld.cpp

HEADERS += helloworld.h\
        helloworld_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

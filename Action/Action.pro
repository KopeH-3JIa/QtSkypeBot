#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T05:07:06
#
#-------------------------------------------------
CONFIG += console
QT -= gui widgets
TARGET = Action
TEMPLATE = lib

DEFINES += ACTION_LIBRARY

SOURCES += action.cpp

HEADERS += action.h\
        action_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

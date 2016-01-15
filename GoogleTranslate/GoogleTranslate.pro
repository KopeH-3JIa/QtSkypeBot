#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T16:33:51
#
#-------------------------------------------------

QT       += network

QT       -= gui

QT += axcontainer
LIBS += -L../Action/release/ -lAction
TARGET = GoogleTranslate
TEMPLATE = lib

DEFINES += GOOGLETRANSLATE_LIBRARY

SOURCES += googletranslate.cpp

HEADERS += googletranslate.h\
        googletranslate_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

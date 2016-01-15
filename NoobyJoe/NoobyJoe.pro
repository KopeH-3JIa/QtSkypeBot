TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

BINPATH = ../../../bin
CONFIG(release, debug|release) {
    BINPATH = $${BINPATH}/release
} else {
    BINPATH = $${BINPATH}/debug
}
QT += core axcontainer
QT -= gui
CONFIG += -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
LIBS += -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
SOURCES += main.cpp \
    client.cpp \
    skype.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    client.h \
    skype.h


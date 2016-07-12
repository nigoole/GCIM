#-------------------------------------------------
#
# Project created by QtCreator 2016-07-12T14:54:55
#
#-------------------------------------------------

QT       -= gui

TARGET = resource
TEMPLATE = lib

DEFINES += LIBRESOURCE_LIBRARY

SOURCES += libresource.cpp

HEADERS += libresource.h\
        libresource_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR     = $$PWD/../libs

MOC_DIR     = $$PWD/../build/lrc
OBJECTS_DIR = $$PWD/../build/lrc
RCC_DIR     = $$PWD/../build/lrc
UI_DIR      = $$PWD/../build/lrc

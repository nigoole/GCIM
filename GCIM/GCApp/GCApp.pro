#-------------------------------------------------
#
# Project created by QtCreator 2016-07-12T14:54:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GCApp
TEMPLATE = app


SOURCES += main.cpp\
        $$PWD/src/mainwindow.cpp

HEADERS  += $$PWD/src/mainwindow.h


#pri fins
include($$PWD/applog/applog.pri)
include($$PWD/emailapi/email.pri)
include($$PWD/myapi/myapi.pri)
include($$PWD/network/network.pri)


INCLUDEPATH         += $$PWD/src


LIBS        += -L$$PWD/../libs -lresource



DESTDIR     = $$PWD/../release

MOC_DIR     = $$PWD/../build/app
OBJECTS_DIR = $$PWD/../build/app
RCC_DIR     = $$PWD/../build/app
UI_DIR      = $$PWD/../build/app

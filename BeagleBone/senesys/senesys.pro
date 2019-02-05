#-------------------------------------------------
#
# Project created by QtCreator 2015-09-08T19:54:43
#
#-------------------------------------------------

QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = senesys
TEMPLATE = app
CONFIG += c++11
LIBS += -lScanAPI

target.path = /home/debian
INSTALLS += target

SOURCES += main.cpp \
    mainwindow.cpp \
    proxy.cpp \
    scanner.cpp \
    senesys.cpp

HEADERS += mainwindow.h \
    proxy.h \
    scanner.h \
    senesys.h \
    ftrScanAPI.h

FORMS += mainwindow.ui

RESOURCES += senesys.qrc

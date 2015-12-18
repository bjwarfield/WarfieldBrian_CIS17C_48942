#-------------------------------------------------
#
# Project created by QtCreator 2015-12-15T09:03:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Graphs
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   +=c++11
TEMPLATE = app


SOURCES += main.cpp \
    GeneralHashFunctions.cpp

HEADERS += \
    graph.h \
    simplevector.h \
    GeneralHashFunctions.h \
    hash.h \
    DoubleLinkedList.h

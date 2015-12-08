TEMPLATE = app
CONFIG += console \
    c++11

CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += main.cpp \
    GeneralHashFunctions.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    hash.h \
    GeneralHashFunctions.h


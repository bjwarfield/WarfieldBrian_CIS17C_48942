TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Stack.h \
    DoubleLinkedList.h \
    Queue.h \
    CircularLinkedList.h \
    LinkedList.h


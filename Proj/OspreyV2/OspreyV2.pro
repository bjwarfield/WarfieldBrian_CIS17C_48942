#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T01:29:56
#
#-------------------------------------------------

include(Entity/entity.pri)
include(Container/container.pri)
include(GameState/gamestate.pri)
include(LevelEditor/leveleditor.pri)
include(Main/main.pri)
include(TileMap/tilemap.pri)
include(Users/users.pri)
include(Util/util.pri)

QT       += core gui
QT      += sql
CONFIG  += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OspreyV2
TEMPLATE = app


SOURCES +=

HEADERS  +=

DISTFILES +=

RESOURCES += \
    resources/resources.qrc

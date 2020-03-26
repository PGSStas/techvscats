#-------------------------------------------------
#
# Project created by QtCreator 2020-03-17T13:53:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = techvscats
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
         main.cpp \
         Controller/controller.cpp \
         Controller/spawner.cpp \
         GameObject/passive_tower.cpp \
         GameObject/active_tower.cpp \
         GameObject/projectile.cpp \
         GameObject/enemy.cpp \
         GameObject/game_object.cpp \
         GameObject/moving_object.cpp \
         GameObject/tower_slot.cpp \
         GameObject/building.cpp \
         GameObject/slow_tower.cpp \
         GameObject/fast_tower.cpp \
         Model/model.cpp \
         Model/road.cpp \
         Model/coordinate.cpp \
         View/view.cpp \
         View/tower_menu.cpp \
         View/tower_menu_option.cpp \

HEADERS += \
         Controller/controller.h \
         Controller/spawner.h \
         GameObject/building.h \
         GameObject/passive_tower.h \
         GameObject/active_tower.h \
         GameObject/projectile.h \
         GameObject/enemy.h \
         GameObject/game_object.h \
         GameObject/moving_object.h \
         GameObject/tower_slot.h \
         GameObject/fast_tower.h \
         GameObject/slow_tower.h \
         Model/model.h \
         Model/road.h \
         Model/coordinate.h \
         Model/wave.h \
         View/view.h \
         View/tower_menu.h \
         View/tower_menu_option.h \

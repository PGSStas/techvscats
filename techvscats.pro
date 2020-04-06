QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = techvscats
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

RESOURCES += resources.qrc

SOURCES += \
         main.cpp \
         Controller/controller.cpp \
         Controller/spawner.cpp \
         GameObject/projectile.cpp \
         GameObject/enemy.cpp \
         GameObject/game_object.cpp \
         GameObject/moving_object.cpp \
         GameObject/building.cpp \
         GameObject/lazer_projectile.cpp \
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
         GameObject/projectile.h \
         GameObject/lazer_projectile.h \
         GameObject/enemy.h \
         GameObject/game_object.h \
         GameObject/moving_object.h \
         Model/model.h \
         Model/road.h \
         Model/coordinate.h \
         Model/enemy_group.h \
         View/view.h \
         View/tower_menu.h \
         View/tower_menu_option.h \

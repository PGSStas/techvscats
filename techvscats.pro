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
         GameObject/auric_field.cpp \
         GameObject/effect.cpp \
         GameObject/base.cpp \
         GameObject/building.cpp \
         Model/model.cpp \
         Model/road.cpp \
         Model/coordinate.cpp \
         Model/size.cpp \
         View/view.cpp \
         View/size_handler.cpp \
         View/tower_menu.cpp \
         View/tower_menu_option.cpp \

HEADERS += \
         Controller/controller.h \
         Controller/spawner.h \
         GameObject/building.h \
         GameObject/projectile.h \
         GameObject/enemy.h \
         GameObject/game_object.h \
         GameObject/moving_object.h \
         GameObject/base.h \
         GameObject/auric_field.h \
         GameObject/effect.h \
         Model/model.h \
         Model/road.h \
         Model/coordinate.h \
         Model/constants.h \
         Model/size.h \
         Model/enemy_group.h \
         View/view.h \
         View/size_handler.h \
         View/tower_menu.h \
         View/tower_menu_option.h \

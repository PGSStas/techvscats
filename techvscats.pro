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
        GameObject/abstract_projectile.cpp \
        GameObject/aimed_projectile.cpp \
        GameObject/auric_field.cpp \
        GameObject/base.cpp \
        GameObject/bomb_projectile.cpp \
        GameObject/building.cpp \
        GameObject/effect.cpp \
        GameObject/enemy.cpp \
        GameObject/game_object.cpp \
        GameObject/lazer_projectile.cpp \
        GameObject/moving_object.cpp \
        Model/coordinate.cpp \
        Model/model.cpp \
        Model/road.cpp \
        Model/size.cpp \
        View/size_handler.cpp \
        View/tower_menu.cpp \
        View/tower_menu_option.cpp \
        View/view.cpp \

HEADERS += \
        Controller/abstract_controller.h \
        Controller/controller.h \
        Controller/spawner.h \
        GameObject/abstract_projectile.h \
        GameObject/aimed_projectile.h \
        GameObject/auric_field.h \
        GameObject/base.h \
        GameObject/bomb_projectile.h \
        GameObject/building.h \
        GameObject/effect.h \
        GameObject/enemy.h \
        GameObject/game_object.h \
        GameObject/lazer_projectile.h \
        GameObject/moving_object.h \
        Model/constants.h \
        Model/coordinate.h \
        Model/enemy_group.h \
        Model/model.h \
        Model/road.h \
        Model/size.h \
        View/size_handler.h \
        View/tower_menu.h \
        View/tower_menu_option.h \
        View/view.h \

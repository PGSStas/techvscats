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
        Controller/multiplayer_client.cpp \
        Controller/spawner.cpp \
        GameObject/abstract_projectile.cpp \
        GameObject/homing_projectile.cpp \
        GameObject/auric_field.cpp \
        GameObject/base.cpp \
        GameObject/bomb_projectile.cpp \
        GameObject/building.cpp \
        GameObject/effect.cpp \
        GameObject/enemy.cpp \
        GameObject/game_object.cpp \
        GameObject/laser_projectile.cpp \
        GameObject/moving_object.cpp \
        GameObject/particle_handler.cpp \
        GameObject/particle.cpp \
        Model/coordinate.cpp \
        Model/model.cpp \
        Model/road.cpp \
        Model/size.cpp \
        Server/server_message.cpp \
        View/animation_player.cpp \
        View/button_handler.cpp \
        View/info_field.cpp \
        View/menu_button.cpp \
        View/size_handler.cpp \
        View/text_notification.cpp \
        View/tower_menu.cpp \
        View/view.cpp \

HEADERS += \
        Controller/abstract_controller.h \
        Controller/controller.h \
        Controller/multiplayer_client.h \
        Controller/spawner.h \
        GameObject/abstract_projectile.h \
        GameObject/homing_projectile.h \
        GameObject/auric_field.h \
        GameObject/base.h \
        GameObject/bomb_projectile.h \
        GameObject/building.h \
        GameObject/effect.h \
        GameObject/enemy.h \
        GameObject/game_object.h \
        GameObject/laser_projectile.h \
        GameObject/moving_object.h \
        GameObject/particle_handler.h \
        GameObject/particle.h \
        Model/constants.h \
        Model/coordinate.h \
        Model/enemy_group.h \
        Model/model.h \
        Model/road.h \
        Model/size.h \
        Server/server_message.h \
        View/animation_player.h \
        View/button_handler.h \
        View/info_field.h \
        View/menu_button.h \
        View/size_handler.h \
        View/text_notification.h \
        View/tower_menu.h \
        View/view.h \

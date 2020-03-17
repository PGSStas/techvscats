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
        Controller/controller.cpp \
        Model/model.cpp \
        main.cpp \
        View/view.cpp

HEADERS += \
        Controller/gameobject.h \
        Controller/controller.h \
        Controller/Mo.h \
        Model/model.h \
        View/view.h \

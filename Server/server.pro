QT += core websockets
QT -= gui

TARGET = echoserver
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    server.cpp \
    message.cpp \
    main.cpp \

HEADERS += \
    server.h \
    message.h \


QT       += core websockets
QT       -= gui

TARGET = echoserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    server.cpp \
    server_message.cpp \
    main.cpp \

HEADERS += \
    server.h \
    server_message.h \

target.path = $$[QT_INSTALL_EXAMPLES]/websockets/echoserver
INSTALLS += target

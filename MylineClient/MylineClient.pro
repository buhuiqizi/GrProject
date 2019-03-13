#-------------------------------------------------
#
# Project created by QtCreator 2019-01-19T15:51:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MylineClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tcpreceiver.cpp \
    landwindow.cpp \
    userinformation.cpp \
    registerwindow.cpp \
    friendlistwindow.cpp \
    common.cpp \
    chatwindow.cpp \
    chatmessage.cpp \
    sqliteconn.cpp

HEADERS += \
        mainwindow.h \
    tcpreceiver.h \
    landwindow.h \
    common.h \
    userinformation.h \
    registerwindow.h \
    friendlistwindow.h \
    chatwindow.h \
    chatmessage.h \
    sqliteconn.h

FORMS += \
        mainwindow.ui \
    landwindow.ui \
    registerwindow.ui \
    friendlistwindow.ui \
    chatwindow.ui

QT += network
QT       += core gui
QT += sql

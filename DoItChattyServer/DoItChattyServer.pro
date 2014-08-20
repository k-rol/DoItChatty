#-------------------------------------------------
#
# Project created by QtCreator 2014-08-16T12:07:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DoItChattyServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    initserver.cpp \
    qbimap.cpp

HEADERS  += mainwindow.h \
    initserver.h \
    qbimap.h

FORMS    += mainwindow.ui
CONFIG += console

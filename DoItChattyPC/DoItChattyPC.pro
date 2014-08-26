#-------------------------------------------------
#
# Project created by QtCreator 2014-08-13T12:28:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DoItChattyPC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpserver.cpp

HEADERS  += mainwindow.h \
    tcpserver.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    images.qrc

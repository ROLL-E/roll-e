#-------------------------------------------------
#
# Project created by QtCreator 2013-11-26T01:24:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cc\
        serverwindow.cc \
        src/*

HEADERS  += serverwindow.h \
         include/*

FORMS    += serverwindow.ui

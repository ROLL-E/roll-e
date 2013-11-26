#-------------------------------------------------
#
# Project created by QtCreator 2013-11-26T01:20:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cc\
        clientwindow.cc \
    src/placeholder.cc




HEADERS  += clientwindow.h \
    include/Skill.h \
    include/ServerConnection.h \
    include/Item.h \
    include/GUI.h \
    include/ClientInventory.h \
    include/Character.h


FORMS    += clientwindow.ui

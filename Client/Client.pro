#-------------------------------------------------
#
# Project created by QtCreator 2013-11-26T01:20:11
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cc\
        clientwindow.cc \
    src/ServerConnection.cc \
    src/Character.cc \
    src/Item.cc \
    src/Skill.cc \
    src/ClientInventory.cc \
    src/placeholder.cc \
    startdialog.cpp \
    ../Server/skillmodel.cpp


HEADERS  += clientwindow.h \
    include/Skill.h \
    include/ServerConnection.h \
    include/Item.h \
    include/GUI.h \
    include/ClientInventory.h \
    include/Character.h \
    startdialog.h \
    ../Server/skillmodel.h

INCLUDEPATH += include
FORMS    += clientwindow.ui \
    startdialog.ui

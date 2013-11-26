#-------------------------------------------------
#
# Project created by QtCreator 2013-11-26T01:24:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cc\
        serverwindow.cc \
    src/placeholder.cc

HEADERS  += serverwindow.h \
    include/ValueBlock.h \
    include/WaitBlock.h \
    include/Story.h \
    include/Skill.h \
    include/Scenario.h \
    include/Ruleset.h \
    include/ModifierBlock.h \
    include/LogicBlock.h \
    include/Item.h \
    include/Inventory.h \
    include/GUI.h \
    include/Fight.h \
    include/DamageBlock.h \
    include/CompareBlock.h \
    include/ClientConnection.h \
    include/Character.h \
    include/ActiveSkill.h \
    include/ActiveItem.h

INCLUDEPATH += include
FORMS    += serverwindow.ui

OTHER_FILES += \
    src/placeholder.txt
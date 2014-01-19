#-------------------------------------------------
#
# Project created by QtCreator 2013-11-26T01:24:56
#
#-------------------------------------------------

# Add more folders to ship with the application, here
folder_01.source = qml/GUI-Scenario
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT       += core gui
QT       += network
QT       += qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cc\
        serverwindow.cc \
    src/placeholder.cc \
    src/WaitBlock.cc \
    src/LogicBlock.cc \
    src/ModifierBlock.cc \
    src/ValueBlock.cc \
    src/DamageBlock.cc \
    src/CompareBlock.cc \
    src/Character.cc \
    src/Story.cc \
    src/Item.cc \
    src/Inventory.cc \
    src/Ruleset.cc \
    src/ClientConnection.cc \
    src/Server.cc \
    src/Fight.cc \
    src/GameSave.cc \
    src/Skill.cc \
    src/Scenario.cc \
    src/scenariocontroller.cpp \
    src/itemmodel.cpp \
    src/skillmodel_QML.cpp \
    characterdialog.cpp \
    skillmodel.cpp \
    itemdialog.cpp \
    startdialog.cc \
    skilldialog.cc

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()


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
    include/ActiveItem.h \
    include/Server.h \
    include/GameSave.h \
    include/scenariocontroller.h \
    include/itemmodel.h \
    include/skillmodel_QML.h \
    characterdialog.h \
    skillmodel.h \
    itemdialog.h \
    startdialog.h \
    skilldialog.h


INCLUDEPATH += include
FORMS    += serverwindow.ui \
    characterdialog.ui \
    itemdialog.ui \
    startdialog.ui \
    skilldialog.ui

OTHER_FILES += \
    src/placeholder.txt

# Add more folders to ship with the application, here
folder_01.source = qml/GUI-Scenario
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
CONFIG += c++11


SOURCES += main.cpp \
    scenariocontroller.cpp \
    ../Server/src/placeholder.cc \
    ../Server/src/ValueBlock.cc \
    ../Server/src/Skill.cc \
    ../Server/src/Ruleset.cc \
    ../Server/src/LogicBlock.cc \
    ../Server/src/Item.cc \
    ../Server/src/Inventory.cc \
    ../Server/src/GameSave.cc \
    ../Server/src/DamageBlock.cc \
    ../Server/src/CompareBlock.cc \
    ../Server/src/Story.cc \
    ../Server/src/Character.cc \
    ../Server/src/WaitBlock.cc \
    ../Server/src/Scenario.cc \
    ../Server/src/ModifierBlock.cc \
    ../Server/src/Fight.cc \
    ../Server/src/Server.cc \
    ../Server/src/ClientConnection.cc \
    itemmodel.cpp \
    skillmodel_QML.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/GUI-Scenario/WaitBlock.qml \
    qml/GUI-Scenario/ModifierBlock.qml \
    qml/GUI-Scenario/DamageBlock.qml \
    qml/GUI-Scenario/EditValue.qml

HEADERS += \
    scenariocontroller.h \
    ../Server/include/GameSave.h \
    ../Server/include/DamageBlock.h \
    ../Server/include/CompareBlock.h \
    ../Server/include/ActiveSkill.h \
    ../Server/include/ActiveItem.h \
    ../Server/include/Story.h \
    ../Server/include/gui_interaction.h \
    ../Server/include/Character.h \
    ../Server/include/WaitBlock.h \
    ../Server/include/Scenario.h \
    ../Server/include/ModifierBlock.h \
    ../Server/include/LogicBlock.h \
    ../Server/include/Fight.h \
    ../Server/include/GUI.h \
    ../Server/include/ClientConnection.h \
    ../Server/include/ValueBlock.h \
    ../Server/include/Skill.h \
    ../Server/include/Ruleset.h \
    ../Server/include/Item.h \
    ../Server/include/Inventory.h \
    ../Server/include/Server.h \
    ../Server/include/ClientConnection.h \
    itemmodel.h \
    skillmodel_QML.h

INCLUDEPATH += ../Server/include

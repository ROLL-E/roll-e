# Add more folders to ship with the application, here
folder_01.source = qml/ROLLE_UI
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

QT += declarative

SOURCES += main.cpp \
    ../Server/src/ValueBlock.cc \
    ../Server/src/WaitBlock.cc \
    ../Server/src/Story.cc \
    ../Server/src/Skill.cc \
    ../Server/src/Scenario.cc \
    ../Server/src/Ruleset.cc \
    ../Server/src/placeholder.cc \
    ../Server/src/ModifierBlock.cc \
    ../Server/src/LogicBlock.cc \
    ../Server/src/Item.cc \
    ../Server/src/Inventory.cc \
    ../Server/src/GameSave.cc \
    ../Server/src/Fight.cc \
    ../Server/src/DamageBlock.cc \
    ../Server/src/CompareBlock.cc \
    ../Server/src/Character.cc

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/ROLLE_UI/Button.qml \
    qml/ROLLE_UI/GameMenu.qml \
    qml/ROLLE_UI/TopMenu.qml \
    qml/ROLLE_UI/SaveLoadMenu.qml \
    images/pergament.jpg \
    qml/ROLLE_UI/LogicBlock.qml \
    qml/ROLLE_UI/LogicBlockSlot.qml \
    qml/ROLLE_UI/CharacterList.qml \
    qml/ROLLE_UI/CharacterDrawer.qml \
    qml/ROLLE_UI/CharacterMenu.qml \
    qml/ROLLE_UI/CharacterContainer.qml \
    qml/ROLLE_UI/PopUpqml \
    qml/ROLLE_UI/PopUp.qml \
    qml/ROLLE_UI/ValueBlock.qml \
    qml/ROLLE_UI/TempRect.qml \
    qml/ROLLE_UI/CompareBlock.qml \
    qml/ROLLE_UI/qmldir \
    qml/ROLLE_UI/blockScript.js

HEADERS += \
    ../Server/include/ValueBlock.h \
    ../Server/include/WaitBlock.h \
    ../Server/include/Story.h \
    ../Server/include/Skill.h \
    ../Server/include/Scenario.h \
    ../Server/include/Ruleset.h \
    ../Server/include/ModifierBlock.h \
    ../Server/include/LogicBlock.h \
    ../Server/include/Item.h \
    ../Server/include/Inventory.h \
    ../Server/include/GUI.h \
    ../Server/include/GameSave.h \
    ../Server/include/Fight.h \
    ../Server/include/DamageBlock.h \
    ../Server/include/CompareBlock.h \
    ../Server/include/ClientConnection.h \
    ../Server/include/Character.h \
    ../Server/include/ActiveSkill.h \
    ../Server/include/ActiveItem.h \
    ../Server/include/person.h

INCLUDEPATH += ../Server/include


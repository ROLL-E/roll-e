import QtQuick 2.0

Rectangle {
    id: mainWindow
    width: 1024
    height: 840

    color: "black"

    Flickable {
        id: characterSheet
        width: parent.width
        height: parent.height-topMenu.height-gameMenu.height
        visible: false
        anchors.top: gameMenu.bottom

        contentWidth: parent.width
        contentHeight: pergamentImage.height



        Image {
            id: pergamentImage
            anchors.top: parent.top

            source: "pergament2.png"

            Text {
                id: text2
                x: 189
                y: 221
                text: "HP: "
                opacity: 0
                font.pixelSize: 12
            }

            TextInput {
                id: text_input1
                x: 417
                y: 439
                width: 80
                height: 20
                text: "40"
                opacity: 0
                font.pixelSize: 12
            }

            Text {
                id: text3
                x: 179
                y: 367
                text: qsTr("Text")
                opacity: 0
                font.pixelSize: 12
            }

            TextInput {
                id: text_input2
                x: 345
                y: 452
                width: 80
                height: 20
                text: qsTr("Text")
                opacity: 0
                font.pixelSize: 12
            }

            Text {
                id: text4
                x: 224
                y: 712
                text: qsTr("Text")
                opacity: 0
                font.pixelSize: 12
            }
        }

    }

    Rectangle {
        id: scenario_temp

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: gameMenu.bottom
        anchors.bottom: parent.bottom

        color: "cyan"

        Text {
            id: text1
            anchors.centerIn: parent
            text: "Här ska det finnas saker sen..."
        }

        LogicBlock {
            id: logicblock1

            colorKey: "red"

            x: 421
            y: 229
            opacity: 0
        }

        LogicBlockSlot {
            id: logicblockslot1

            colorKey: "red"
            x: 605
            y: 226
            opacity: 0
        }

        LogicBlock {
            id: logicblock2

            colorKey: "blue"
            blockLabel: "OB"
            x: 370
            y: 344
            opacity: 0
        }

        LogicBlockSlot {
            id: logicblockslot2

            colorKey: "blue"
            x: 550
            y: 344
            opacity: 0
        }


        visible: false

    }

    TopMenu {
        id: topMenu
        anchors.top: mainWindow.top
    }

    GameMenu {
        id: gameMenu
        anchors.top: topMenu.bottom

        visible: true
    }

    SaveLoadMenu {
        id: saveLoadMenu
        anchors.top: topMenu.bottom

        visible: false
    }





    states: [
        State {
            name: "SAVE/LOAD"

            PropertyChanges {
                target: saveLoadMenu
                visible: true
            }

            PropertyChanges {
                target: gameMenu
                visible: false
            }

            PropertyChanges {
                target: characterSheet
                visible: false
            }
        },
        State {
            name: "GAME_CHARACTER"

            PropertyChanges {
                target: gameMenu

                characterButtonActive: true
                scenarioButtonActive: false
                fightButtonActive: false

            }

            PropertyChanges {
                target: characterSheet
                visible: true

            }

            PropertyChanges {
                target: pergamentImage
                sourceSize.width: 1026
                clip: false
            }

            PropertyChanges {
                target: text_input1
                x: 312
                y: 321
                font.family: "Papyrus"
                selectionColor: "#000000"
                font.pointSize: 50
                opacity: 1
            }

            PropertyChanges {
                target: text2
                x: 178
                y: 240
                text: "HP"
                font.family: "Papyrus"
                font.pointSize: 50
                font.bold: true
                opacity: 1
            }

            PropertyChanges {
                target: scenario_temp
                x: 0
                y: 146
                anchors.bottomMargin: -6
                anchors.leftMargin: 0
                anchors.topMargin: 6
                anchors.rightMargin: 0
            }

            PropertyChanges {
                target: text3
                x: 179
                y: 371
                text: qsTr("SP")
                font.pointSize: 50
                font.family: "Papyrus"
                opacity: 1
            }

            PropertyChanges {
                target: text_input2
                x: 312
                y: 446
                text: qsTr("33")
                font.family: "Papyrus"
                font.pointSize: 50
                opacity: 1
            }

            PropertyChanges {
                target: text4
                x: 224
                y: 852
                text: qsTr("Other fun stuff...")
                font.pointSize: 50
                font.family: "Papyrus"
                opacity: 1
            }


        },
        State {
            name: "GAME_SCENARIO"

            PropertyChanges {
                target: gameMenu

                characterButtonActive: false
                scenarioButtonActive: true
                fightButtonActive: false

            }

            PropertyChanges {
                target: characterSheet
                visible: false
            }

            PropertyChanges {
                target: scenario_temp
                x: 246
                y: 312
                visible: true
                opacity: 1
            }

            PropertyChanges {
                target: logicblock1
                x: 456
                y: 226
                opacity: 1
            }

            PropertyChanges {
                target: text1
                x: 268
                y: 262
                text: "Bara ett test..."
                anchors.horizontalCenterOffset: -172
                anchors.verticalCenterOffset: -81
            }

            PropertyChanges {
                target: logicblockslot1
                opacity: 1
            }

            PropertyChanges {
                target: logicblock2
                opacity: 1
            }

            PropertyChanges {
                target: logicblockslot2
                opacity: 1
            }

        },
        State {
            name: "GAME_FIGHT"

            PropertyChanges {
                target: characterSheet
                visible: false
            }

            PropertyChanges {
                target: gameMenu

                characterButtonActive: false
                scenarioButtonActive: false
                fightButtonActive: true

            }
        }
    ]
}

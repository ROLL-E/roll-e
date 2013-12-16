import QtQuick 2.0
import QtQuick.Dialogs 1.0


Rectangle {
    id: mainWindow

    state: "CHARACTER"

    width: 1248
    height: 840

    color: "black"

    PopUp {
        id: openFilePopUp

        width: 400
        height: 250

        title: "File Loaded"

        Rectangle {
            color: "black"

            anchors.fill: parent
        }

        Text {
            anchors.centerIn: parent
            color: "green"
            text: fileDialog.fileUrl
        }
    }

    FileDialog {
        id: fileDialog
        nameFilters: [ "Text files (*.txt)" ]
        onAccepted: openFilePopUp.visible = true
    }

    TopMenu {
        id: topMenu
        anchors.top: parent.top
    }

    CharacterList {
        id: characterList


        anchors.top : topMenu.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.margins:  10

        width: 300
    }

    GameMenu {
        id: gameMenu

        anchors.top: topMenu.bottom
        anchors.left: parent.left
        anchors.right: characterList.left

        anchors.margins: 10

        height: 100
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#000000"
            }

            GradientStop {
                position: 1
                color: "#5d949c"
            }
        }
    }

    Rectangle {
        id: characterContainer

        color: "blue"

        anchors.top: gameMenu.bottom
        anchors.left: parent.left
        anchors.right: characterList.left
        anchors.bottom: parent.bottom

        anchors.margins: 10


        Rectangle {
            id: currentPlayer


            color: "lightblue"

            height: 50

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.margins: 20

            Text {
                anchors.centerIn: parent

                font.pointSize: 18
                font.bold: true
                font.underline: true

                text: "Player 1"
            }
        }

        CharacterMenu {
            id: characterMenu

            anchors.top: currentPlayer.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.margins: 20
        }

        Rectangle {
            id: characterSheet

            visible: characterMenu.activeState === "Attributes"

            color: "lightblue"

            anchors.top: characterMenu.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.margins: 20

            ListView {
                id: attributeList
                width: 253

                clip: true

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left

                anchors.margins: 20


                delegate: Item {
                    anchors.left: parent.left
                    height: 40
                    Row {
                        id: row1

                        Text {
                            text: name
                            font.bold: true
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        TextEdit {
                            text: value
                            font.bold: true
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        spacing: 10
                    }
                }
                model: ListModel {
                    ListElement {
                        name: "HP"
                        value: "100"
                    }

                    ListElement {
                        name: "SP"
                        value: "40"
                    }

                    ListElement {
                        name: "Dex"
                        value: "20"
                    }

                    ListElement {
                        name: "Strength"
                        value: "15"
                    }
                }
            }
        }

        Rectangle {
            id: invetnory

            visible: characterMenu.activeState === "Inventory"

            color: "lightblue"

            anchors.top: characterMenu.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.margins: 20

            Rectangle {
                id: itemSelectorContainer
                height: 120

                color: "blue"

                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top

                anchors.margins: 20

                GridView {
                    id: itemSelector

                    anchors.top: parent.top
                    anchors.right: addItemButton.left
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom


                    anchors.margins: 10

                    clip: true

                    delegate: Item {
                        id: itemInSelector
                        x: 5
                        height: 50
                        Column {



                            Rectangle {
                                id: crectItem
                                width: 60
                                height: 60
                                color: colorCode
                                border.width: 2
                                border.color: "black"
                                anchors.horizontalCenter: parent.horizontalCenter

                                Text {
                                    text: name

                                    anchors.centerIn: parent
                                    font.bold: true
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                            }

                            spacing: 5
                        }
                    }
                    cellHeight: 80
                    model: ListModel {
                        ListElement {
                            name: "Grey"
                            colorCode: "grey"
                        }

                        ListElement {
                            name: "Red"
                            colorCode: "red"
                        }

                        ListElement {
                            name: "Blue"
                            colorCode: "blue"
                        }

                        ListElement {
                            name: "Green"
                            colorCode: "green"
                        }

                        ListElement {
                            name: "Grey"
                            colorCode: "grey"
                        }

                        ListElement {
                            name: "Red"
                            colorCode: "red"
                        }

                        ListElement {
                            name: "Blue"
                            colorCode: "blue"
                        }

                        ListElement {
                            name: "Green"
                            colorCode: "green"
                        }

                        ListElement {
                            name: "Grey"
                            colorCode: "grey"
                        }

                        ListElement {
                            name: "Red"
                            colorCode: "red"
                        }

                        ListElement {
                            name: "Blue"
                            colorCode: "blue"
                        }

                        ListElement {
                            name: "Green"
                            colorCode: "green"
                        }
                    }
                    cellWidth: 70
                }

                Button {
                    id: addItemButton

                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom

                    width: parent.height - 40

                    anchors.margins: 20
                    label: "+"
                }

            }



            Rectangle {
                id: itemDetails
                color: "blue"
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                anchors.top: itemSelectorContainer.bottom
                anchors.topMargin: 20
            }

        }

        Rectangle {
            id: skills

            color: "lightblue"

            visible: characterMenu.activeState === "Skills"

            anchors.top: characterMenu.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.margins: 20


            Rectangle {
                id: skillSelectorContainer
                height: 120

                color: "blue"

                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top

                anchors.margins: 20

                GridView {
                    id: skillSelector

                    anchors.top: parent.top
                    anchors.right: addSkillButton.left
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom

                    anchors.margins: 10

                    clip: true

                    delegate: Item {
                        id: skillInSelector
                        x: 5
                        height: 50
                        Column {

                            Rectangle {
                                id: crectSkill
                                width: 60
                                height: 60
                                color: colorCode
                                border.width: 2
                                border.color: "black"
                                anchors.horizontalCenter: parent.horizontalCenter

                                Text {
                                    text: name
                                    font.bold: true

                                    anchors.centerIn: parent
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                            }

                            spacing: 5
                        }
                    }
                    cellHeight: 80
                    model: ListModel {

                        ListElement {
                            name: "Red"
                            colorCode: "red"
                        }

                        ListElement {
                            name: "Blue"
                            colorCode: "blue"
                        }

                        ListElement {
                            name: "Green"
                            colorCode: "green"
                        }

                        ListElement {
                            name: "Grey"
                            colorCode: "grey"
                        }

                        ListElement {
                            name: "Red"
                            colorCode: "red"
                        }

                        ListElement {
                            name: "Blue"
                            colorCode: "blue"
                        }

                        ListElement {
                            name: "Green"
                            colorCode: "green"
                        }

                        ListElement {
                            name: "Grey"
                            colorCode: "grey"
                        }

                        ListElement {
                            name: "Red"
                            colorCode: "red"
                        }

                        ListElement {
                            name: "Blue"
                            colorCode: "blue"
                        }

                        ListElement {
                            name: "Green"
                            colorCode: "green"
                        }
                    }
                    cellWidth: 70
                }

                Button {
                    id: addSkillButton

                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom

                    width: parent.height - 40

                    anchors.margins: 20
                    label: "+"
                }

            }

            Rectangle {
                id: skillDetails
                color: "blue"
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                anchors.top: skillSelectorContainer.bottom
                anchors.topMargin: 20
            }

        }


    }

    Rectangle {
        id: scenarioContainer

        color: "blue"

        anchors.top: gameMenu.bottom
        anchors.left: parent.left
        anchors.right: characterList.left
        anchors.bottom: parent.bottom

        anchors.margins: 10

        Rectangle {
            id: selectScenarioContainer
            height: 150
            color: "lightblue"

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            GridView {
                id: scenarioGridView
                anchors.fill: parent
                anchors.topMargin: 20

                clip: true
                cellHeight: 90
                cellWidth: 100

                delegate: Item {
                    width:scenarioGridView.cellWidth;
                    height: scenarioGridView.cellHeight

                    Rectangle {
                        width: 60
                        height: 60
                        color: colorCode
                        anchors.horizontalCenter: parent.horizontalCenter

                        Text {
                            text: name
                            font.bold: true
                            anchors.centerIn: parent
                        }
                    }
                }




                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                    }

                    ListElement {
                        name: "Green"
                        colorCode: "green"
                    }
                }

            }
        }

        Rectangle {
            id: configureScenarioContainer

            color: "lightblue"
            anchors.top: selectScenarioContainer.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.margins: 20

            Rectangle {
                id: logicBlockContainer
                color: "blue"

                width: 150

                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                anchors.margins: 10

            }

            Rectangle {
                id: logicTreeEditor
                color: "black"

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: logicBlockContainer.left
                anchors.bottom: parent.bottom

                anchors.margins: 10

                Rectangle {
                    id: startBlock
                    y: 170
                    width: 100
                    height: 100
                    color: "green"

                    radius: 50
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        anchors.centerIn: parent
                        text: "Start"
                    }
                }

            }
        }
    }

    Rectangle {
        id: fightContainer

        color: "blue"

        anchors.top: gameMenu.bottom
        anchors.left: parent.left
        anchors.right: characterList.left
        anchors.bottom: parent.bottom

        anchors.margins: 10

        Rectangle {
            id: orderContainer
            color: "lightblue"

            width: 200

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            anchors.margins: 10

            ListView {
                id: characterOrderView
                anchors.topMargin: 20
                anchors.fill: parent

                clip: true



                delegate: Item {
                    x: parent.x + 10
                    height: 100
                    width: 100

                    Row {
                        spacing: 10

                        Item {
                            width: 80
                            height: 80

                            Image {
                                visible: currentCharacter
                                anchors.centerIn: parent
                                source: "arrow-right.png"
                            }
                        }

                        Rectangle {
                            width: 80
                            height: 80
                            color: colorCode

                            Text {
                                text: name
                                font.bold: true
                                anchors.centerIn: parent
                            }

                        }
                    }


                }
                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                        currentCharacter: false
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                        currentCharacter: false
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                        currentCharacter: true
                    }

                    ListElement {
                        name: "Green"
                        colorCode: "green"
                        currentCharacter: false
                    }
                }
            }

        }

        Rectangle {
            id: runnningScenarioContainer
            color: "lightblue"

            height: 200

            anchors.top: parent.top
            anchors.left: orderContainer.right
            anchors.right: parent.right

            anchors.margins: 10

            Rectangle {
                id: fightStatusBox
                color: "green"

                height: 80

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right

                anchors.margins: 10

                Text {
                    id: fightStatusText

                    anchors.centerIn: parent

                    font.pointSize: 20
                    text: "Running scenario _instert_name_here_"
                }


            }

            Rectangle {
                id: fightControllContainer
                color: "blue"

                anchors.top: fightStatusBox.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                anchors.margins: 10

                Row {
                    id: fightControllButtonRow

                    anchors.centerIn: parent
                    spacing: 100

                    Button {
                        id: stopScenarioInFightButton
                        buttonHeight: 50
                        buttonWidth: 200

                        label: "Stop"
                    }

                    Button {
                        id: continueInFightButton
                        buttonHeight: 50
                        buttonWidth: 200

                        label: "Continue"
                    }
                }

            }
        }

        Rectangle {
            id:backgroundScenorioContainer
            color: "lightblue"

            anchors.top: runnningScenarioContainer.bottom
            anchors.left: orderContainer.right
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.margins: 10

            ListView {
                id: backgroundScenarioView

                anchors.topMargin: 10
                anchors.fill: parent

                clip: true

                delegate: Item {
                    x: 5
                    height: 70
                    Row {
                        id: row2
                        spacing: 10
                        Rectangle {
                            width: backgroundScenorioContainer.width - 10
                            height: 60
                            color: colorCode

                            Text {
                                text: name
                                anchors.centerIn: parent
                                font.bold: true
                            }

                            Rectangle {
                                color: "yellow"

                                width: parent.height - 20
                                height: parent.height - 20

                                anchors.right: parent.right
                                anchors.top: parent.top
                                anchors.bottom: parent.bottm

                                anchors.margins: 10

                                Text {
                                    anchors.centerIn: parent

                                    text: turnsLeft
                                }

                            }
                        }


                    }
                }
                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                        turnsLeft: 4
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                        turnsLeft: 2
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                        turnsLeft: 1
                    }

                }
            }


        }

    }
    states: [
        State {
            name: "CHARACTER"

            PropertyChanges {
                target: scenarioContainer
                visible: false
            }

            PropertyChanges {
                target: fightContainer
                visible: false
            }

            PropertyChanges {
                target: fightControllContainer
                x: 10
                y: 102
                anchors.topMargin: 12
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.bottomMargin: 8
            }
        },
        State {
            name: "FIGHT"

            PropertyChanges {
                target: characterContainer
                visible: false
            }

            PropertyChanges {
                target: scenarioContainer
                visible: false
            }

            PropertyChanges {
                target: fightContainer
                visible: true
            }
        },
        State {
            name: "SCENARIO"

            PropertyChanges {
                target: characterContainer
                visible: false
            }

            PropertyChanges {
                target: scenarioContainer
            }

            PropertyChanges {
                target: fightContainer
                visible: false
            }
        }
    ]


}

//Rectangle {
//    id: mainWindow
//    width: 1024
//    height: 840

//    color: "black"


//    Item {
//        id: gameContainer
//        anchors.top: topMenu.bottom
//        anchors.right: parent.right
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left
//        anchors.topMargin: 0

//        GameMenu {
//            id: gameMenu
//            x: 0
//            y: 0

//            gradient: Gradient {
//                GradientStop {
//                    position: 0
//                    color: "#939393"
//                }

//                GradientStop {
//                    position: 1
//                    color: "#000000"
//                }
//            }

//            anchors.top: parent.top
//            visible: true
//        }

//        Rectangle {
//            id: scenario_temp
//            x: 0
//            y: 0

//            anchors.left: parent.left
//            anchors.right: parent.right
//            anchors.top: gameMenu.bottom
//            anchors.bottom: parent.bottom

//            color: "cyan"

//            Text {
//                id: text1
//                anchors.centerIn: parent
//                text: "Här ska det finnas saker sen..."
//            }

//            LogicBlock {
//                id: logicblock1

//                colorKey: "red"

//                x: 421
//                y: 229
//                opacity: 0
//            }

//            LogicBlockSlot {
//                id: logicblockslot1

//                colorKey: "red"
//                x: 605
//                y: 226
//                opacity: 0
//            }

//            LogicBlock {
//                id: logicblock2

//                colorKey: "blue"
//                blockLabel: "OB"
//                x: 370
//                y: 344
//                opacity: 0
//            }

//            LogicBlockSlot {
//                id: logicblockslot2

//                colorKey: "blue"
//                x: 550
//                y: 344
//                opacity: 0
//            }


//            visible: false

//        }

//    }

//    Item {
//        id: characterContainer
//        x: 388
//        y: 329
//        anchors.right: characterList.left
//        anchors.rightMargin: 0
//        anchors.left: parent.left
//        anchors.leftMargin: 0
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 0
//        anchors.top: topMenu.bottom
//        anchors.topMargin: 0

//        CharacterMenu {
//            id: characterMenu
//            x: 0
//            y: 0


//            gradient: Gradient {
//                GradientStop {
//                    position: 0
//                    color: "#939393"
//                }

//                GradientStop {
//                    position: 1
//                    color: "#000000"
//                }
//            }

//            visible: false
//            anchors.right: parent.right
//            anchors.rightMargin: 0
//            anchors.left: parent.left
//            anchors.leftMargin: 0
//            anchors.top: parent.top
//            anchors.topMargin: 0
//    }

//        Flickable {
//            id: characterSheet
//            width: parent.width
//            height: parent.height-topMenu.height-gameMenu.height
//            anchors.topMargin: 0
//            visible: false
//            anchors.top: characterMenu.bottom

//            contentWidth: parent.width
//            contentHeight: pergamentImage.height



//            Image {
//                id: pergamentImage
//                visible: true
//                anchors.top: parent.top

//                source: "pergament2.png"

//                TextInput {
//                    id: text_input1
//                    x: 230
//                    y: 183
//                    width: 80
//                    height: 20
//                    text: qsTr("Text")
//                    font.pixelSize: 12
//                    opacity: 0
//                }

//                TextInput {
//                    id: text_input2
//                    x: 354
//                    y: 178
//                    width: 80
//                    height: 20
//                    text: qsTr("Text")
//                    font.pixelSize: 12
//                    opacity: 0
//                }

//                Text {
//                    id: text2
//                    x: 265
//                    y: 69
//                    text: qsTr("Text")
//                    font.pixelSize: 12
//                    opacity: 0
//                }

//                Text {
//                    id: text3
//                    x: 220
//                    y: 336
//                    text: qsTr("Text")
//                    font.pixelSize: 12
//                    opacity: 0
//                }

//                Text {
//                    id: text4
//                    x: 391
//                    y: 69
//                    text: qsTr("Text")
//                    font.pixelSize: 12
//                    opacity: 0
//                }
//            }

//        }

//    }

//    Item {
//        id: saveLoadContainer
//        anchors.top: topMenu.bottom
//        anchors.topMargin: 0
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 0
//        anchors.right: parent.right
//        anchors.rightMargin: 0
//        anchors.left: parent.left
//        anchors.leftMargin: 0

//        opacity: 0

//        SaveLoadMenu {
//            id: saveLoadMenu
//            x: 0
//            y: 0

//            gradient: Gradient {
//                GradientStop {
//                    position: 0
//                    color: "#939393"
//                }

//                GradientStop {
//                    position: 1
//                    color: "#000000"
//                }
//            }

//            anchors.top: parent.top
//            visible: false
//    }

//    }



//    TopMenu {
//        id: topMenu
//        anchors.top: mainWindow.top


//    }

//    CharacterList {
//        id: characterList
//        anchors.topMargin: 40
//        width: 300
//        anchors.right: parent.right
//        anchors.rightMargin: 0

//        anchors.top: parent.top
//        anchors.bottom: mainWindow.bottom
//        anchors.left: characterDrawer.right
//    }


//}

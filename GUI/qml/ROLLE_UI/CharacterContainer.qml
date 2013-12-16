import QtQuick 2.0

Rectangle {

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

        color: "lightblue"

        anchors.top: characterMenu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.margins: 20

        ListView {
            id: attributeList
            width: 253

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

                anchors.fill: parent

                anchors.margins: 0

                clip: true

                delegate: Item {
                    id: itemInSelector
                    x: 5
                    height: 50
                    Column {

                        Text {
                            x: 5
                            text: name
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Rectangle {
                            id: crectItem
                            width: 60
                            height: 60
                            color: colorCode
                            border.width: 2
                            border.color: "black"
                            anchors.horizontalCenter: parent.horizontalCenter
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

                anchors.fill: parent

                anchors.margins: 0

                clip: true

                delegate: Item {
                    id: skillInSelector
                    x: 5
                    height: 50
                    Column {

                        Text {
                            x: 5
                            text: name
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Rectangle {
                            id: crectSkill
                            width: 60
                            height: 60
                            color: colorCode
                            border.width: 2
                            border.color: "black"
                            anchors.horizontalCenter: parent.horizontalCenter
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

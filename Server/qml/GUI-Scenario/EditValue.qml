import QtQuick 2.0

Rectangle {
    id: valueEditor

    property bool valueVisible: false
    property int blocknumber: 1

    signal hideEditor()

    anchors.fill: parent

    color: "black"


    Rectangle {
        id: editorTitleBox

        anchors.top : parent.top
        anchors.left : parent.left
        anchors.right: parent.right
        anchors.margins: 10

        height: 50

        radius: 5
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: "white";
            }
            GradientStop {
                position: 1.00;
                color: "gray";
            }
        }

        Text {
            anchors.centerIn: parent
            font.pointSize: 20
            text: "Edit Valueblock"
        }

    }

    Rectangle {
        id: intentionContainer

        anchors.top: editorTitleBox.bottom
        anchors.left: parent.left
        anchors.margins: 10

        height: 250
        width: 200

        color: "silver"

        radius: 5
        z: 1

        Rectangle {
            id: intentionTitleBox

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.margins: 10

            height: 50

            color: "silver"
            border.width: 2
            border.color: "blue"

            radius: 5

            Text {
                anchors.centerIn: parent

                font.pointSize: 18
                text: "Intention"
            }

        }

        Button {
            id: valueButton
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: intentionTitleBox.bottom
            anchors.margins: 20

            buttonHeight: 40
            buttonWidth: 130

            label: "Value"

            onButtonClicked: {
                valueContainer.visible = true
                rollContainer.visible = false
                bonusContainer.visible = false

                valueWindow.width = 430

                controller.set_valueblock_intention("s", valueEditor.blocknumber)

            }

        }
        Button {
            id: rollButton
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: valueButton.bottom
            anchors.margins: 10

            buttonHeight: 40
            buttonWidth: 130

            label: "Roll"

            onButtonClicked: {
                valueContainer.visible = false
                rollContainer.visible = true
                bonusContainer.visible = false

                valueWindow.width = 430

                controller.set_valueblock_intention("r", valueEditor.blocknumber)
            }

        }
        Button {
            id: allButton
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: rollButton.bottom
            anchors.margins: 10

            buttonHeight: 40
            buttonWidth: 130

            label: "All"

            onButtonClicked: {
                valueContainer.visible = false
                rollContainer.visible = true
                bonusContainer.visible = true

                valueWindow.width = 1010

                controller.set_valueblock_intention("a", valueEditor.blocknumber)

            }

        }
    }

    Rectangle {
        id: valueContainer
        anchors.top: editorTitleBox.bottom
        anchors.left: intentionContainer.right
        anchors.bottom: intentionContainer.bottom
        anchors.margins: 10
        anchors.bottomMargin: 0

        width: 200

        color: "gray"

        radius: 5
        anchors.leftMargin: 10
        visible: false

        Rectangle {
            id: valueTitleBox
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10

            height: 50

            color: "silver"

            radius: 5

            Text {
                anchors.centerIn: parent

                font.pointSize: 18

                text: "Enter value"
            }
        }

        Rectangle {
            anchors.top: valueTitleBox.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10

            height: 50

            color: "white"

            radius: 5

            TextInput {
                id: valueInput
                anchors.centerIn: parent

                validator: RegExpValidator { regExp: /\d+/ }

                font.pointSize: 18

                text: "0"
            }
        }

    }

    Rectangle {
        id: rollContainer
        x: 220
        y: 70
        anchors.top: editorTitleBox.bottom
        anchors.left: intentionContainer.right
        anchors.bottom: intentionContainer.bottom
        anchors.margins: 10
        anchors.bottomMargin: 0

        width: 200

        color: "gray"
        anchors.topMargin: 10
        visible: false
        anchors.leftMargin: 10

        radius: 5


        Rectangle {
            id: sidesTitleBox

            anchors.top: rollContainer.top
            anchors.left: parent.left
            anchors.right:  parent.right
            anchors.margins: 10

            height: 50

            color: "silver"

            radius: 5

            Text {
                id: diceSidesTitle

                anchors.centerIn: parent

                font.pointSize: 18

                text: "Sides"
            }
        }

        Button {
            id: decreseSidesButton

            anchors.left: parent.left
            anchors.top: sidesTitleBox.bottom
            anchors.margins: 10

            buttonHeight: 40
            buttonWidth: 40

            buttonColor: "red"

            label:  "-"

            onButtonClicked: {
                if (diceSidesText.diceSides > 1) {
                    diceSidesText.diceSides--
                }
            }
        }


        Button {
            id: increseSidesButton

            anchors.right: parent.right
            anchors.top: sidesTitleBox.bottom
            anchors.margins: 10

            buttonHeight: 40
            buttonWidth: 40

            buttonColor: "green"

            label:  "+"

            onButtonClicked: {
                diceSidesText.diceSides++
            }
        }

        Rectangle {

            anchors.top: sidesTitleBox.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            anchors.margins: 10
            height: 40
            width: 40

            radius: 5

            Text {
                id: diceSidesText

                property int diceSides: 6

                anchors.centerIn: parent

                font.pointSize: 18

                text: diceSides
            }
        }


        Rectangle {
            id: numberTitleBox

            anchors.top: increseSidesButton.bottom
            anchors.left: parent.left
            anchors.right:  parent.right
            anchors.margins: 10

            height: 50

            color: "silver"

            radius: 5

            Text {
                id: diceNumberTitle

                anchors.centerIn: parent

                font.pointSize: 18

                text: "Number"
            }
        }

        Button {
            id: decreseNumberButton

            anchors.left: parent.left
            anchors.top: numberTitleBox.bottom
            anchors.margins: 10

            buttonHeight: 40
            buttonWidth: 40

            buttonColor: "red"

            label:  "-"

            onButtonClicked: {
                if (diceNumberText.diceNumber > 0) {
                    diceNumberText.diceNumber--
                }
            }
        }


        Button {
            id: increseNumberButton

            anchors.right: parent.right
            anchors.top: numberTitleBox.bottom
            anchors.margins: 10

            buttonHeight: 40
            buttonWidth: 40

            buttonColor: "green"

            label:  "+"

            onButtonClicked: {
                diceNumberText.diceNumber++
            }
        }

        Rectangle {
            anchors.top: numberTitleBox.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            anchors.margins: 10
            height: 40
            width: 40

            radius: 5

            Text {
                id: diceNumberText

                property int diceNumber: 1

                anchors.centerIn: parent

                font.pointSize: 18

                text: diceNumber
            }
        }
    }

    Rectangle {
        id: bonusContainer
        x: 430
        y: 70
        anchors.top: editorTitleBox.bottom
        anchors.left: valueContainer.right
        anchors.bottom: intentionContainer.bottom
        anchors.margins: 10
        anchors.bottomMargin: 0

        width: 360
        height: 250

        color: "gray"

        radius: 5
        visible: false
        anchors.leftMargin: 10
        anchors.topMargin: 10

        Rectangle {
            id: attributeContainer

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 10

            width: 110

            radius: 5

            Text {
                id: attributeListTitle
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 10

                font.pointSize: 14
                font.bold: true

                text: "Attributes"
            }

            ListView {
                id: attributeList

                anchors.top: attributeListTitle.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.topMargin: 10
                anchors.bottomMargin: 10

                clip: true


                delegate: Rectangle {
                    id: listDelegateAttribute
                    property bool selected: false

                    height: 25
                    width: 100

                    border.width: 2
                    border.color: mouseAreaAttribute.pressed ? "black" : "white"

                    color: selected ? "lightgreen" : "white"
                    Text {
                        anchors.centerIn: parent
                        text: modelData
                    }

                    MouseArea {
                        id: mouseAreaAttribute
                        anchors.fill: parent
                        onClicked: {
                            listDelegateAttribute.selected = !listDelegateAttribute.selected
                            if (listDelegateAttribute.selected === true) {
                                controller.add_attribute_valueblock(modelData, valueEditor.blocknumber)
                            } else {
                                controller.remove_attribute_valueblock(modelData, valueEditor.blocknumber)
                            }

                        }

                    }
                }
                model: controller.attributes


            }
        }

        Rectangle {
            id: skillContainer

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.margins: 10

            width: 110

            radius: 5

            Text {
                id: skillListTitle
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 10

                font.pointSize: 14
                font.bold: true

                text: "Skills"
            }

            ListView {
                id: skillList

                anchors.top: skillListTitle.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.topMargin: 10
                anchors.bottomMargin: 10

                clip: true

                delegate: Rectangle {
                    id: listDelegateSkill
                    property bool selected: false

                    height: 40
                    width: 100

                    border.width: 2
                    border.color: mouseAreaSkill.pressed ? "black" : "white"

                    color: selected ? "lightblue" : "white"
                    Item {
                        anchors.fill: parent
                        Text {
                            id: skillName

                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: parent.top
                            anchors.topMargin: 5

                            font.bold: true

                            text: model.modelData.name
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: skillName.bottom

                            font.italic: true

                            text:  model.modelData.modifier
                        }
                    }

                    MouseArea {
                        id: mouseAreaSkill
                        anchors.fill: parent

                        onClicked: {
                            listDelegateSkill.selected = !listDelegateSkill.selected
                            if (listDelegateSkill.selected === true) {
                                controller.add_skill_valueblock(model.modelData.skill ,model.modelData.modifier, valueEditor.blocknumber)
                            } else {
                                controller.remove_skill_valueblock(model.modelData.skill, model.modelData.modifier,  valueEditor.blocknumber)
                            }

                        }

                    }
                }
                model: controller.skills


            }


        }

        Rectangle {
            id: inventoryContainer

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            width: 110
            anchors.margins: 10

            radius: 5

            Text {
                id: inventoryListTitle
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 10

                font.pointSize: 14
                font.bold: true

                text: "Items"
            }

            ListView {
                id: inventoryList

                anchors.top: inventoryListTitle.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.topMargin: 10
                anchors.bottomMargin: 10

                clip: true

                delegate: Rectangle {
                    id: listDelegateInventory
                    property bool selected: false

                    height: 40
                    width: 100

                    border.width: 2
                    border.color: mouseAreaInventory.pressed ? "black" : "white"



                    color: selected ? "lightcoral" : "white"
                    Item {
                        anchors.fill: parent
                        Text {
                            id: itemName

                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: parent.top
                            anchors.topMargin: 5

                            font.bold: true

                            text: model.modelData.name
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: itemName.bottom

                            font.italic: true

                            text:  model.modelData.attribute
                        }
                    }

                    MouseArea {
                        id: mouseAreaInventory
                        anchors.fill: parent

                        onClicked: {
                            listDelegateInventory.selected = !listDelegateInventory.selected
                            if (listDelegateInventory.selected === true) {
                                controller.add_item_valueblock(model.modelData.item_id, model.modelData.attribute, valueEditor.blocknumber)
                            } else {
                                controller.remove_item_valueblock(model.modelData.name, model.modelData.attribute, model.modelData.item_id, valueEditor.blocknumber)
                            }

                        }

                    }
                }
                model: controller.items


            }
        }


    }

    Rectangle {
        anchors.top: editorTitleBox.bottom
        anchors.left: bonusContainer.right
        anchors.bottom: intentionContainer.bottom
        anchors.margins: 10
        anchors.bottomMargin: 0

        width: 200

        color: "gray"

        radius: 5

        Rectangle {
            anchors.fill: parent
            anchors.margins: 10

            color: "white"
            radius: 5

            Component {
                id: contactDelegate
                Item {
                    property string characterName: modelData
                    width: 180; height: 40
                    Text {
                        id: characterText
                        font.pointSize: 16
                        anchors.centerIn: parent
                        text: characterName }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            parent.ListView.view.currentIndex = index
                        }
                    }

                }
            }

            ListView {
                id: selectCharacterList
                anchors.fill: parent
                model: controller.all_characters
                delegate: contactDelegate
                highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                focus: true
                clip: true

            }

        }


    }

    Button{
        anchors.top: intentionContainer.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        height: 50

        radius: 5

        label: "DONE"

        onButtonClicked: {
            if (valueContainer.visible === true) {
                controller.set_valueblock_value(valueInput.text, valueEditor.blocknumber)
            }else if (rollContainer.visible === true) {
                controller.set_valueblock_roll(diceSidesText.diceSides, diceNumberText.diceNumber, valueEditor.blocknumber)
            }

            controller.set_valueblock_target(selectCharacterList.currentItem.characterName, root.blockNumber)

            hideEditor()


        }

    }




}

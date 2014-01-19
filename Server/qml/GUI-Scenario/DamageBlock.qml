import QtQuick 2.0

import "blockScript.js" as BlockScript


Item {
    id: damageBlock
    property string colorKey
    property int blockNumberParent

    LogicBlock {
        id: root

        onNewBlock: {
            BlockScript.newDamageBlock(colorKey, counter)
        }

        colorKey: damageBlock.colorKey
        blockNumber: blockNumberParent
        blockLabel: "D"

        slotType: "damageblock"

    }

    PopUp {

        visible: root.editmode
        id: openDamageEdit

        width: 200
        height: 320

        title: "Edit Damage Block"

        color: "black"

        Rectangle {
            id: selectCharacterTitleBox
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.margins: 10

            height: 40

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

                font.pointSize: 18

                text: "Select character"
            }

        }


        Rectangle {
            id: selectCharacterListContainer
             anchors.top: selectCharacterTitleBox.bottom
             anchors.left: parent.left
             anchors.right: parent.right

             anchors.margins: 10

             height: 200

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

        Button {
            anchors.top: selectCharacterListContainer.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.margins: 10

            buttonHeight: 40

            label: "DONE"

            onButtonClicked: {
                controller.set_damegeblock_target(selectCharacterList.currentItem.characterName, root.blockNumber)
                root.editmode = false
            }

        }




    }


}

import QtQuick 2.0
import "blockScript.js" as BlockScript
import QtQuick.Controls 1.0


Item {
    id: valueBlock
    property string colorKey

    property int blockNumberParent

    LogicBlock {
        id: root

        slotType: "valueblock"

        onNewBlock: {
            BlockScript.newValueBlock(colorKey, counter)
        }

        blockNumber: blockNumberParent
        colorKey: valueBlock.colorKey
        blockLabel: "V"

    }

    PopUp {

        visible: root.editmode
        id: openValueEdit

        width: 200
        height: 150

        title: "Edit Value Block"

        Rectangle {
            color: "grey"

            anchors.fill: parent

            CheckBox {
                id: enabledCheck

                text: "Random"
                checked: true
                anchors.bottom: staticValue.top
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle
            {
                id:staticValue
                anchors.centerIn: parent
                color: "white"

                height: 50
                width: 200

                TextInput {
                    id:staticValueInput
                    anchors.centerIn: parent
                    text: "Enter static value here!"
                }
            }

            Button {
                anchors.horizontalCenter:  parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20

                onClicked: {

                    editValueBlock(staticValueInput.text, enabledCheck.checked, root.blockNumber)
                    root.editmode = false
                }


            }


        }


    }


}



import QtQuick 2.0
import QtQuick.Controls 1.0

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

    }

    PopUp {

        visible: root.editmode
        id: openDamageEdit

        width: 300
        height: 150

        title: "Edit Damage Block"

        Rectangle {
            color: "grey"

            anchors.fill: parent

            CheckBox {
                id: enabledCheck


                text: "Extra Bad"
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
                    text: "I kill you!"
                }
            }

            Button {
                anchors.horizontalCenter:  parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20

                onClicked: {

                    editDamageBlock(staticValueInput.text, enabledCheck.checked, root.blockNumber)
                    root.editmode = false
                }


            }


        }


    }


}

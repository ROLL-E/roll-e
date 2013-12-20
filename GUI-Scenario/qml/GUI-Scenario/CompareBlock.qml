import QtQuick 2.0

import "blockScript.js" as BlockScript
import QtQuick.Controls 1.0


Item {
    id: compareBlock
    property string colorKey
    property int blockNumberParent

    LogicBlock {
        id: root

        onNewBlock: {
            BlockScript.newCompareBlock(colorKey , counter)
        }

        colorKey: compareBlock.colorKey
        blockNumber: blockNumberParent
        blockLabel: "C"
        slotType: "compareblock"



    }
    PopUp {

        visible: root.editmode
        id: openValueEdit

        width: 200
        height: 150

        title: "Edit Compare Block"

        Rectangle {
            color: "grey"

            anchors.fill: parent


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
                    text: "Compareblock settings"
                }
            }

            Button {
                anchors.horizontalCenter:  parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20

                onClicked: {

                    root.editmode = false
                    editCompareBlock(staticValueInput.text, false, root.blockNumber)
                }


            }


        }


    }

}

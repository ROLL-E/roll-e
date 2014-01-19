import QtQuick 2.0
import "blockScript.js" as BlockScript


Item {
    id: valueBlockOutputRoot
    property string colorKey
    property bool moved: false

    MouseArea {
        id: mouseArea

        width: 20; height: 20

        drag.target: block

        Item{
            id: dummy

            anchors.centerIn: parent
            visible: false
        }


        onReleased: {
            if(mouseArea.drag.target !== dummy){
                parent = block.Drag.target !== null ? block.Drag.target : valueBlockOutputRoot
            }

            if (block.Drag.target !== null && moved === false){
                //signal c++ to add pointer to valueblock nr blockNumber

                controller.set_block_value(blockNumber)

                BlockScript.newValueBlockOutput(colorKey)
                moved = true

                mouseArea.drag.target = dummy
            }
        }

        Rectangle {
            id: block

            width: 20; height: 20
            radius: 10

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            color: !moved ? colorKey : "lightblue"

            Drag.keys: [ colorKey ]
            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: 10
            Drag.hotSpot.y: 10


            states: State {
                when: mouseArea.drag.active
                ParentChange { target: block; parent: valueBlockOutputRoot }
                AnchorChanges { target: block; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
            }

        }

    }

}

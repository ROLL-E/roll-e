
import QtQuick 2.0
import "blockScript.js" as BlockScript


Item {
    id: root

    property string colorKey
    property string blockLabel: "LB"
    property string slotType: "default"

    property bool moved: false

    signal newBlock()

    width: 64; height: 64

    MouseArea {
        id: mouseArea

        width: 64; height: 64
        anchors.centerIn: parent

        drag.target: block

        onReleased: {
            //haxx
            if(parent !== root) {
                drag.target = dummy
            }else {
                parent = block.Drag.target !== null ? block.Drag.target : root
                newBlock()

                // resize tree editor

                logicTreeEditorContainer.editorWidth = logicTreeEditorContainer.editorWidth + 64

                if(slotType === "compareblock") {
                    logicTreeEditorContainer.editorHeight = logicTreeEditorContainer.editorHeight + 80
                }

            }


        }


        Rectangle {
            id: block

            width: 64; height: 64
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            color: colorKey

            Drag.keys: [ colorKey ]
            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: 32
            Drag.hotSpot.y: 32

            Text {
                anchors.fill: parent
                color: "white"
                font.pixelSize: 48
                text: root.blockLabel
                horizontalAlignment:Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            states: State {
                when: mouseArea.drag.active
                ParentChange { target: block; parent: root }
                AnchorChanges { target: block; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
            }

        }

        Item {
            id:dummy
            visible: false
        }

        LogicBlockSlot {
            visible: slotType === "default" && mouseArea.parent !== root && !mouseArea.drag.active

            height: block.height
            width: block.width
            colorKey: root.colorKey
            x: block.x + 80
            y: block.y
        }

        LogicBlockSlot {
            visible: slotType === "compareblock" && mouseArea.parent !== root && !mouseArea.drag.active

            height: block.height
            width: block.width
            colorKey: root.colorKey
            x: block.x + 80
            y: block.y + 40
        }

        LogicBlockSlot {
            visible: slotType === "compareblock" && mouseArea.parent !== root && !mouseArea.drag.active

            height: block.height
            width: block.width
            colorKey: root.colorKey
            x: block.x + 80
            y: block.y - 40
        }


    }
}


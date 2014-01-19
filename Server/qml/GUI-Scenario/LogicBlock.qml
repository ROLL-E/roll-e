
import QtQuick 2.0
import "blockScript.js" as BlockScript


Item {
    id: root

    property string colorKey
    property string blockLabel: "LB"
    property string slotType: "default"

    property int blockX
    property int blockY

    property int blockNumber
    property bool editmode: false


    property bool moved: false

    signal newBlock()

    width: 64; height: 64

    MouseArea {
        id: mouseArea

        width: 64; height: 64
        anchors.centerIn: parent

        drag.target: block

        onClicked: {
            if(moved) {
            editmode = true
            }
        }

        Item{
            id: dummy
            visible: false
        }


        onReleased: {

            if(mouseArea.drag.target !== dummy){
                parent = block.Drag.target !== null ? block.Drag.target : root
            }

            if (block.Drag.target !== null && moved === false)
            {

                incrementCounter()

                // add block to c++ scenario
                controller.add_block(blockNumber, blockLabel)

                newBlock()
                mouseArea.drag.target = dummy
                moved = true

                // resize tree editor

                logicTreeEditorContainer.editorWidth = logicTreeEditorContainer.editorWidth + 64

                if(slotType === "compareblock") {
                    logicTreeEditorContainer.editorHeight = logicTreeEditorContainer.editorHeight + 140
                }
            }
        }


        Rectangle {
            id: block


            width: 64; height: 64
            radius: 5

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


        LogicBlockSlot {
            visible: (slotType === "default" || slotType == "valueblock" || slotType === "damageblock") && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {

                controller.set_active_block_number(blockNumber)
                controller.set_active_block_side("none")
            }

            height: block.height
            width: block.width
            colorKey: root.colorKey
            x: block.x + 80
            y: block.y
        }

        LogicBlockSlot {
            visible: slotType === "compareblock" && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {

                controller.set_active_block_number(blockNumber)
                controller.set_active_block_side("rhs")
            }


            height: block.height
            width: block.width
            colorKey: (lhsValue.hasValue && rhsValue.hasValue) ? root.colorKey : "purple"
            x: block.x + 80
            y: block.y + 80
        }

        LogicBlockSlot {
            visible: slotType === "compareblock" && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {

                controller.set_active_block_number(blockNumber)
                controller.set_active_block_side("lhs")
            }

            height: block.height
            width: block.width
            colorKey: (lhsValue.hasValue && rhsValue.hasValue) ? root.colorKey : "purple"
            x: block.x + 80
            y: block.y - 80
        }

        LogicBlockSlot {
            id: lhsValue

            //hasValue is true if the slot has any additional children, kind of a hack... there should be some better way of doing this
            property bool hasValue: children[2] !== undefined

            visible: slotType === "compareblock" && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {
                controller.set_active_block_number(blockNumber)
                controller.set_active_block_side("lhs")
            }

            height: 20
            width: 20

            dropRound: true

            colorKey: "green"
            x: block.x + block.width/2 - width/2
            y: block.y - 30 - width


        }

        LogicBlockSlot {
            id: rhsValue

            property bool hasValue: children[2] !== undefined

            visible: slotType === "compareblock" && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {

                controller.set_active_block_number(blockNumber)
                controller.set_active_block_side("rhs")
            }

            height: 20
            width: 20

            dropRound: true

            colorKey: "green"
            x: block.x + block.width/2 - width/2
            y: block.y + 30 + block.height
        }

        LogicBlockSlot {
            id: damageValue

            isDamage: true

            //hasValue is true if the slot has any additional children, kind of a hack... there should be some better way of doing this
            property bool hasValue: children[2] !== undefined

            visible: slotType === "damageblock" && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {
                controller.set_active_block_number(blockNumber)
                controller.set_active_block_side("none")
            }

            height: 20
            width: 20

            dropRound: true

            colorKey: "green"
            x: block.x + block.width/2 - width/2
            y: block.y - 30 - width


        }



        ValueBlockOutput {
           visible: slotType === "valueblock" && mouseArea.parent !== root && !mouseArea.drag.active

           colorKey: "green"


           x: block.x + block.width/2 - 10
           y: block.y - 30
        }

    }
}



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

        onClicked: editmode = true

        Item{
            id: dummy
            visible: false
        }


        onReleased: {

            if(mouseArea.drag.target !== dummy){
                parent = block.Drag.target !== null ? block.Drag.target : root
            }

            if (block.Drag.target !== null)
            {
                incrementCounter()

                // add block to c++
                add_block(blockNumber, blockLabel)

                newBlock()
                mouseArea.drag.target = dummy
                moved = true


                //Create the scenario



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

            Text {
                anchors.left: parent.left
                anchors.right: parent.right

                text:blockNumber
            }

            states: State {
                when: mouseArea.drag.active
                ParentChange { target: block; parent: root }
                AnchorChanges { target: block; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
            }

        }


        LogicBlockSlot {
            visible: (slotType === "default" || slotType == "valueblock") && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {

                setDropAreaParent(blockNumber)
                setDropAreaSide("none")
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

                setDropAreaParent(blockNumber)
                setDropAreaSide("rhs")
            }


            height: block.height
            width: block.width
            colorKey: root.colorKey
            x: block.x + 80
            y: block.y + 80
        }

        LogicBlockSlot {
            visible: slotType === "compareblock" && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {

                setDropAreaParent(blockNumber)
                setDropAreaSide("lhs")
            }

            height: block.height
            width: block.width
            colorKey: root.colorKey
            x: block.x + 80
            y: block.y - 80
        }

        LogicBlockSlot {
            id: lhsValue
            visible: slotType === "compareblock" && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {

                setDropAreaParent(blockNumber)
                setDropAreaSide("lhs")
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
            visible: slotType === "compareblock" && mouseArea.parent !== root && !mouseArea.drag.active

            onEntered: {

                setDropAreaParent(blockNumber)
                setDropAreaSide("rhs")
            }

            height: 20
            width: 20

            dropRound: true

            colorKey: "green"
            x: block.x + block.width/2 - width/2
            y: block.y + 30 + block.height
        }



        ValueBlockOutput {
           visible: slotType === "valueblock" && mouseArea.parent !== root && !mouseArea.drag.active

           colorKey: "green"


           x: block.x + block.width/2 - 10
           y: block.y - 30
        }

    }
}


import QtQuick 2.0

Rectangle {
    id: scenarioContainer

    property int counter: 4

    signal testSignal(string msg)
    signal incrementCounter()

    signal setDropAreaParent(int blocknumber)
    signal setDropAreaSide(string side)

    signal add_block(int number, string type)
    signal editValueBlock(string satval, bool intet, int blocknr)

    visible: sController.showEditor

    onIncrementCounter: counter++

    color: "blue"

    width:  800
    height: 600

    Rectangle {
        id: configureScenarioContainer

        color: "lightblue"
        z: 1
       anchors.fill: parent

        anchors.margins: 20

        Flickable {
            id: logicTreeEditorContainer

            property int editorWidth: 500
            property int editorHeight: 300

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: logicBlockContainer.left
            anchors.bottom: parent.bottom

            anchors.margins: 10

            contentHeight: logicTreeEditor.height
            contentWidth: logicTreeEditor.width

            clip: true

            Rectangle {
                id: logicTreeEditor
                color: "black"
                z: -1

                width: logicTreeEditorContainer.width > logicTreeEditorContainer.editorWidth ? logicTreeEditorContainer.width : logicTreeEditorContainer.editorWidth
                height: logicTreeEditorContainer.height > logicTreeEditorContainer.editorHeight ? logicTreeEditorContainer.height : logicTreeEditorContainer.editorHeight

                anchors.top: parent.top
                anchors.left: parent.left

                Rectangle {
                    id: startBlock
                    width: 100
                    height: 100
                    color: "green"

                    radius: 50

                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        anchors.centerIn: parent
                        text: "Start"
                    }
                }

                LogicBlockSlot {
                    id: logicblockslot1
                    anchors.left: parent.left
                    anchors.leftMargin: 150
                    anchors.verticalCenter: parent.verticalCenter

                    colorKey: "red"
                }

            }

        }


        Rectangle {
            id: logicBlockContainer
            color: "blue"

            width: 150

            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.margins: 10

            ValueBlock {
                id: valueblock
                x: 40
                y: 33

                blockNumberParent: 1
                colorKey: "red"
            }

            CompareBlock {
                id: compareBlock
                x: 40
                y: 131
                blockNumberParent: 2
                colorKey: "red"
            }

            DamageBlock {
                id: damageblock1
                x: 40
                y: 230
                blockNumberParent: 3
                colorKey: "red"
            }

            WaitBlock {
                id: waitblock
                x: 40
                y: 328
                blockNumberParent: 4
                colorKey: "red"
            }


        }
    }

}

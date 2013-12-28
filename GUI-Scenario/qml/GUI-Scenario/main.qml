import QtQuick 2.0

Rectangle {
    id: scenarioContainer


    property int counter: 4

    signal testSignal(string msg)
    signal incrementCounter()

    //visible: sController.showEditor

    onIncrementCounter: counter++

    color: "black"

    width:  500
    height: 450

    Row {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.topMargin: 10
        anchors.rightMargin: 10

        height: 40
        spacing: 10

        Button {
            buttonWidth: parent.width/3 - 10
            buttonHeight: parent.height

            label: "Save"
        }

        Button {
            buttonWidth: parent.width/3 - 10
            buttonHeight: parent.height

            label: "New"

            // placeholder
            onButtonClicked: logicblockslot1.visible = false
        }

        Button {
            buttonWidth: parent.width/3 - 10
            buttonHeight: parent.height

            label: "Exit"

            onButtonClicked: Qt.quit()
        }
    }

    Rectangle {
        id: configureScenarioContainer

        color: "lightblue"
        z: 1
        anchors.fill: parent
        anchors.margins: 20
        anchors.topMargin: 60

        radius: 5

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

                    border.width: 5
                    border.color:  Qt.lighter(color)

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

            radius: 5

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

//            WaitBlock {
//                id: waitblock
//                x: 40
//                y: 328
//                blockNumberParent: 4
//                colorKey: "red"
//            }


        }
    }

}

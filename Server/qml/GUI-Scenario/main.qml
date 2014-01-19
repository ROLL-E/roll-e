import QtQuick 2.0

Rectangle {
    id: scenarioContainer


    property int counter: 4
    property bool mainVisible: false

    signal testSignal(string msg)
    signal incrementCounter()

    onIncrementCounter: counter++

    color: "black"

    width:  500
    height: 450

    Item {
        anchors.fill: parent
        visible: mainVisible

        Item {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.topMargin: 10
            anchors.rightMargin: 10

            height: 40

            Button {
                buttonWidth: parent.width - 10
                buttonHeight: parent.height

                label: "DONE"
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



    Rectangle {
        id: nameWindow
        visible: !mainVisible

        color: "black"

        anchors.centerIn: parent
        height: 220
        width: 170

        Rectangle{
            id: nameWindoeTextContainer

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

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.margins: 10
            height: 50

            Text{
                id: nameWindowText
                anchors.top: parent.top
                anchors.centerIn: parent
                font.pointSize: 18
                text: "Enter Name:"
            }
        }


        Rectangle {
            id: nameWindoeInputContainer
            anchors.top: nameWindoeTextContainer.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.margins: 10
            height: 50


            color: "white"
            radius: 5


            TextInput {
                id: nameWindowInput
                font.pointSize: 17
                anchors.fill: parent
                anchors.topMargin: 10
            }

        }



        Button {
            anchors.top: nameWindoeInputContainer.bottom
            anchors.left: parent.left
            anchors.margins: 10
            label: "DONE"

            onButtonClicked: {
                mainVisible = true
                controller.set_name(nameWindowInput.text)

            }
        }
    }


}

import QtQuick 2.0

Rectangle {
    color: "#343434"

    // Model
    ListModel {
        id: characterModel

        ListElement {
            name:"Player 1"
        }

    }

    Component {
        id: listDelegate

        Item {
            id: delegateItem
            width: listView.width
            height: 80

            clip:true


            Column {
                id: arrows
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                Image {
                    source: "arrow_up.png"
                    MouseArea { anchors.fill: parent; onClicked: characterModel.move(index, index-1, 1) }
                }
                Image { source: "arrow_down.png"
                    MouseArea { anchors.fill: parent; onClicked: characterModel.move(index, index+1, 1) }
                }
            }

            Column {
                anchors {
                    left: arrows.right
                    horizontalCenter: parent.horizontalCenter;
                    bottom: parent.verticalCenter
                }

                Text {
                    anchors.left: parent.horizontalCenter
                    text: name
                    font.pixelSize: 15
                    color: "white"
                }

            }

            ListView.onAdd: SequentialAnimation {
                PropertyAction { target: delegateItem; property: "height"; value: 0 }
                NumberAnimation { target: delegateItem; property: "height"; to: 80; duration: 250; easing.type: Easing.InOutQuad }
            }

            ListView.onRemove: SequentialAnimation {
                PropertyAction { target: delegateItem; property: "ListView.delayRemove"; value: true }
                NumberAnimation { target: delegateItem; property: "height"; to: 0; duration: 250; easing.type: Easing.InOutQuad }

                // Make sure delayRemove is set back to false so that the item can be destroyed
                PropertyAction { target: delegateItem; property: "ListView.delayRemove"; value: false }
            }
        }
   }


    ListView {
        id: listView

        clip: true

        anchors {
            left: parent.left; top: parent.top;
            right: parent.right; bottom: buttons.top;
            margins: 20
        }
        model: characterModel
        delegate: listDelegate
    }

    Row {
        id: buttons
        anchors { left: parent.left; bottom: parent.bottom; margins: 20 }
        spacing: 40

        Button {
            label: "Add a character"
            labelSize: 10
            buttonHeight: 25
            buttonWidth: 120
            onButtonClicked: {
                characterModel.append({
                    "name": "player2",
                })
            }
        }

        Button {
            label: "Remove all"
            labelSize: 10
            buttonHeight: 25
            buttonWidth: 100
            onButtonClicked: characterModel.clear()
        }

    }
}

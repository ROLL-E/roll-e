
import QtQuick 2.0

DropArea {
    id: dragTarget

    property alias dropProxy: dragTarget
    property string colorKey

    width: 64; height: 64
    keys: [ colorKey ]

    Rectangle {
        id: dropRectangle

        anchors.fill: parent
        color: "transparent"

        border.width: 2
        border.color: colorKey


        states: [
            State {
                when: dragTarget.containsDrag
                PropertyChanges {
                    target: dropRectangle
                    color: "grey"
                }
            }
        ]
    }
}


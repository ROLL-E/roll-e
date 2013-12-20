
import QtQuick 2.0

DropArea {
    id: dragTarget
    property alias dropProxy: dragTarget
    property string colorKey
    property int dropWidth: 64
    property int dropHeight: 64

    property bool dropRound: false


    width: dropWidth; height: dropHeight
    keys: [ colorKey ]

    Rectangle {
        id: dropRectangle

        radius: dropRound ? height/2 : 5

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


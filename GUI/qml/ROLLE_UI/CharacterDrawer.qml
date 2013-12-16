import QtQuick 2.0

Rectangle {
    id: drawer

    property bool drawerOpen: false
    property int xPos
    property int listWidth

    height: parent.height
    width: 30

    color : "gray"

    radius: 3

    x: drawerOpen ? xPos - listWidth - drawer.width : xPos - drawer.width

    MouseArea {
       id: drawerMouseArea

       anchors.fill: parent
       onClicked: {
           drawerOpen = !drawerOpen
        }
    }

    Behavior on x {
        NumberAnimation { target: drawer; property: "x"; duration: 500; easing.type: Easing.OutElastic }
    }
}


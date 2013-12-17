import QtQuick 2.0

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

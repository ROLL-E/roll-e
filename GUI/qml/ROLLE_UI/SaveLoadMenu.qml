import QtQuick 2.0

Rectangle {
    width: parent.width
    height: 100

    Row {
        anchors.centerIn: parent

        spacing: parent.width / 6

        Button {
            id: saveMenuButton
            label: "Save"

        }

        Button {
            id: loadMenuButton
            label: "Load"

        }


    }

}

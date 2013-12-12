import QtQuick 2.0

Rectangle {
    width: parent.width
    height: 100
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#939393"
        }

        GradientStop {
            position: 1
            color: "#000000"
        }
    }

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

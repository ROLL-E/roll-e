import QtQuick 2.0

Rectangle {

    width: parent.width
    height: 40

    color: "darkgray"
    border.width: 2
    border.color: "black"

    Row {
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10

        width: 320
        spacing: width / 6

        Button {
            id: settingsMenuButton

            labelSize: 6
            label: "Settings"

            buttonColor: "purple"

            buttonWidth: 80
            buttonHeight: 30

        }

        Button {
            id: saveLoadMenuButton

            labelSize: 6
            label: "Save/Load"


            buttonWidth: 80
            buttonHeight: 30

            onButtonClicked: mainWindow.state = "SAVE/LOAD"

        }

        Button {
            id: exitMenuButton

            labelSize: 6
            label: "Exit"

            buttonWidth: 80
            buttonHeight: 30

            buttonColor: "red"

            onButtonClicked: Qt.quit()
        }

    }
}

import QtQuick 2.0

Rectangle {
    id: button


    // propertys can be used from outside this file

    property int buttonHeight: 75
    property int buttonWidth: 150

    property string label: "Button Label"
    property color textColor: buttonLabel.color

    property color borderOnHoverColor: "lightgray"
    property color borderColor: "transparent"

    property color buttonColor: "gray"

    property real labelSize: 14

    // signals

    signal buttonClicked()


    radius: 6
    antialiasing: true
    border.width: 2
    border.color: borderColor
    width: buttonWidth
    height: buttonHeight

    Text {
        id:buttonLabel
        anchors.centerIn: parent
        // use property label in parent as text
        text: button.label

        color: "white"
        font.pointSize: button.labelSize

    }

    MouseArea {
        id:buttonMouseArea
        anchors.fill: parent

        onClicked: buttonClicked()

        hoverEnabled: true
        onEntered: parent.border.color = borderOnHoverColor
        onExited: parent.border.color = borderColor

    }

    color: buttonMouseArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor

    // animate colorchange
    Behavior on color { ColorAnimation { duration: 50 } }

    // for 3D effect, scale button down when pressed
    scale: !buttonMouseArea.pressed ? 1.0 : 0.9
    Behavior on scale { NumberAnimation { duration: 50 } }
}

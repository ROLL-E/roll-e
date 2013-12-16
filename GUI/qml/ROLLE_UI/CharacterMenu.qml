import QtQuick 2.0

Rectangle {
    property bool characterButtonActive: false
    property bool scenarioButtonActive: false
    property bool fightButtonActive: false

    id: characterMenu
    height: 100

    Row {
        anchors.centerIn: parent
        spacing: parent.width / 6

        Button {
            id: attributesMenuButton
            label: "Attributes"

            color: gameMenu.scenarioButtonActive ? "green" : buttonColor

            onButtonClicked: mainWindow.state = "CHARACTER_ATTRIBUTES"

        }

        Button {
            id: inventoryMenuButton
            label: "Inventory"

            color: gameMenu.fightButtonActive ? "green" : buttonColor

            onButtonClicked: mainWindow.state = "CHARACTER_INVENTORY"

        }

        Button {
            id: skillsMenuButton
            label: "Skills"

            color: gameMenu.fightButtonActive ? "green" : buttonColor

            onButtonClicked: mainWindow.state = "CHARACTER_SKILLS"

        }

    }

}

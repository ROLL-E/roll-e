import QtQuick 2.0

Rectangle {
    property bool characterButtonActive: false
    property bool scenarioButtonActive: false
    property bool fightButtonActive: false

    id: gameMenu
    width: parent.width

    Row {
        spacing: 60

        anchors.centerIn: parent
        Button {
            id: characterMenuButton
            label: "Character"

            color: gameMenu.fightButtonActive ? "green" : buttonColor

            onButtonClicked: mainWindow.state = "CHARACTER"

        }


        Button {
            id: fightMenuButton
            label: "Fight"

            color: gameMenu.fightButtonActive ? "green" : buttonColor

            onButtonClicked: mainWindow.state = "FIGHT"

        }

        Button {
            id: scenarioMenuButton
            label: "Scenario"

            color: gameMenu.scenarioButtonActive ? "green" : buttonColor

            onButtonClicked: mainWindow.state = "SCENARIO"

        }

    }

}


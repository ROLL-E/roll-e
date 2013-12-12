import QtQuick 2.0

Rectangle {
    property bool characterButtonActive: false
    property bool scenarioButtonActive: false
    property bool fightButtonActive: false

    id: gameMenu
    width: parent.width
    height: 100
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#939393"
        }

        GradientStop {
            position: 1
            color: "blue"
        }
    }

    Row {
        anchors.centerIn: parent

        // spacing for 3 buttons
        spacing: parent.width / 6

        Button {
            id: characterMenuButton
            label: "Character"

            color: gameMenu.characterButtonActive ? "green" : buttonColor

            onButtonClicked: mainWindow.state = "GAME_CHARACTER"

        }

        Button {
            id: scenarioMenuButton
            label: "Scenario"

            color: gameMenu.scenarioButtonActive ? "green" : buttonColor

            onButtonClicked: mainWindow.state = "GAME_SCENARIO"

        }

        Button {
            id: fightMenuButton
            label: "Fight"

            color: gameMenu.fightButtonActive ? "green" : buttonColor

            onButtonClicked: mainWindow.state = "GAME_FIGHT"

        }

    }

}


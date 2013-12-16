import QtQuick 2.0

Rectangle {
    property string activeState

    id: characterMenu
    height: 100

    state: "ATTRIBUTES"

    Row {
        anchors.centerIn: parent
        spacing: parent.width / 6

        Button {
            id: attributesMenuButton
            label: "Attributes"

            color: gameMenu.scenarioButtonActive ? "green" : buttonColor

            onButtonClicked: characterMenu.state = "ATTRIBUTES"

        }

        Button {
            id: inventoryMenuButton
            label: "Inventory"

            color: gameMenu.fightButtonActive ? "green" : buttonColor

            onButtonClicked: characterMenu.state = "INVENTORY"

        }

        Button {
            id: skillsMenuButton
            label: "Skills"

            color: gameMenu.fightButtonActive ? "green" : buttonColor

            onButtonClicked: characterMenu.state = "SKILLS"

        }

    }
    states: [
        State {
            name: "ATTRIBUTES"
            PropertyChanges {
                target: characterMenu
                activeState: "Attributes"

            }
        },
        State {
            name: "SKILLS"

            PropertyChanges {
                target: characterMenu
                activeState: "Skills"
            }
        },
        State {
            name: "INVENTORY"
            PropertyChanges {
                target: characterMenu
                activeState: "Inventory"
            }
        }
    ]

}

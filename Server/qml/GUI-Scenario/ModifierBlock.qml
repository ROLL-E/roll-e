import QtQuick 2.0
import "blockScript.js" as BlockScript


Item {
    id: modifierBlock
    property string colorKey

    LogicBlock {
        id: root

        onNewBlock: {
            BlockScript.newValueBlock(colorKey, counter)
        }

        colorKey: waitBlock.colorKey
        blockNumber: blockNumberParent
        blockLabel: "W"

    }

}

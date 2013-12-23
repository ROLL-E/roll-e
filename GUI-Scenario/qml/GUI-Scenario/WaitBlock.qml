import QtQuick 2.0
import "blockScript.js" as BlockScript


Item {
    id: waitBlock
    property string colorKey
    property int blockNumberParent

    LogicBlock {
        id: root

        onNewBlock: {
            BlockScript.newWaitBlock(colorKey, counter)
        }

        colorKey: waitBlock.colorKey
        blockNumber: blockNumberParent
        blockLabel: "W"

    }

}

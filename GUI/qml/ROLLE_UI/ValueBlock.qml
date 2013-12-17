import QtQuick 2.0
import "blockScript.js" as BlockScript


Item {
    id: valueBlock
    property string colorKey

    LogicBlock {
        id: root

        onNewBlock: {
            BlockScript.newValueBlock(colorKey)
        }

        colorKey: valueBlock.colorKey
        blockLabel: "V"

    }

}



import QtQuick 2.0

import "blockScript.js" as BlockScript


Item {
    id: compareBlock
    property string colorKey

    LogicBlock {
        id: root

        onNewBlock: {
            BlockScript.newCompareBlock(colorKey)
        }

        colorKey: compareBlock.colorKey
        blockLabel: "C"
        slotType: "compareblock"

    }

}

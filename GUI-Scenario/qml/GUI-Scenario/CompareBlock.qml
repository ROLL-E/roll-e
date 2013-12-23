import QtQuick 2.0

import "blockScript.js" as BlockScript
import QtQuick.Controls 1.0


Item {
    id: compareBlock
    property string colorKey
    property int blockNumberParent

    LogicBlock {
        id: root

        onNewBlock: {
            BlockScript.newCompareBlock(colorKey , counter)
        }

        colorKey: compareBlock.colorKey
        blockNumber: blockNumberParent
        blockLabel: "C"
        slotType: "compareblock"
    }

}

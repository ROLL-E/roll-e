import QtQuick 2.0
import "blockScript.js" as BlockScript


Item {
    id: damageBlock
    property string colorKey
    property int blockNumberParent

    LogicBlock {
        id: root

        onNewBlock: {
            BlockScript.newDamageBlock(colorKey, counter)
        }

        colorKey: damageBlock.colorKey
        blockNumber: blockNumberParent
        blockLabel: "D"

    }

}

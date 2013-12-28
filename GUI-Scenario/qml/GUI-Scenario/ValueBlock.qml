import QtQuick 2.0
import "blockScript.js" as BlockScript
import QtQuick.Controls 1.0


Item {
    id: valueBlock
    property string colorKey

    property int blockNumberParent

    LogicBlock {
        id: root

        slotType: "valueblock"

        onNewBlock: {
            BlockScript.newValueBlock(colorKey, counter)
        }

        blockNumber: blockNumberParent
        colorKey: valueBlock.colorKey
        blockLabel: "V"

    }

    PopUp {
        id: valueWindow

        visible: root.editmode

        width: 220
        height: 400
        EditValue {
            id: valueEditor
            blocknumber: root.blockNumber

            onHideEditor: root.editmode = false
        }

    }



}



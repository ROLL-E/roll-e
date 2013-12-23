var component;
var block;

function newLogicBlock() {
    component = Qt.createComponent("LogicBlock.qml")
    block = component.createObject(root);

    if(block == null) {
        console.log("Error creating object")
    }
}

function newValueBlock(colorKey, count) {
    component = Qt.createComponent("ValueBlock.qml")
    block = component.createObject(root, {"colorKey":colorKey, "blockNumberParent":count});

    if(block == null) {
        console.log("Error creating object")
    }
}


function newCompareBlock(colorKey, count) {
    component = Qt.createComponent("CompareBlock.qml")
    block = component.createObject(root, {"colorKey":colorKey, "blockNumberParent":count});

    if(block == null) {
        console.log("Error creating object")
    }
}

function newWaitBlock(colorKey, count) {
    component = Qt.createComponent("WaitBlock.qml")
    block = component.createObject(root, {"colorKey":colorKey, "blockNumberParent":count});

    if(block == null) {
        console.log("Error creating object")
    }
}

function newDamageBlock(colorKey, count) {
    component = Qt.createComponent("DamageBlock.qml")
    block = component.createObject(root, {"colorKey":colorKey, "blockNumberParent":count});

    if(block == null) {
        console.log("Error creating object")
    }
}

function newModifierBlock(colorKey, count) {
    component = Qt.createComponent("ModifierBlock.qml")
    block = component.createObject(root, {"colorKey":colorKey, "blockNumberParent":count});

    if(block == null) {
        console.log("Error creating object")
    }
}

function newValueBlockOutput(colorKey) {
    component = Qt.createComponent("ValueBlockOutput.qml")
    block = component.createObject(valueBlockOutputRoot, {"colorKey":colorKey});

    if(block == null) {
        console.log("Error creating object")
    }
}




var component;
var block;

function newLogicBlock() {
    component = Qt.createComponent("LogicBlock.qml")
    block = component.createObject(root);

    if(block == null) {
        console.log("Error creating object")
    }
}

function newValueBlock(colorKey) {
    component = Qt.createComponent("ValueBlock.qml")
    block = component.createObject(root, {"colorKey":colorKey});

    if(block == null) {
        console.log("Error creating object")
    }
}

function newCompareBlock(colorKey) {
    component = Qt.createComponent("CompareBlock.qml")
    block = component.createObject(root, {"colorKey":colorKey});

    if(block == null) {
        console.log("Error creating object")
    }
}



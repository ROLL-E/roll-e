#include "ModifierBlock.h"
#include <iostream>

using namespace std;

ModifierBlock::ModifierBlock(ModifierBlock& other) {
    target = other.target;
    previous_modifier = other.previous_modifier;
    modifiers = other.modifiers;
}

void ModifierBlock::set_target(Character* new_target) {
    target = new_target;
}

Character* ModifierBlock::get_target() const {
    return target;
}

map<string, int> ModifierBlock::get_modifiers() const {
    return modifiers;
}

void ModifierBlock::set_modifier(string name, int value) {
    modifiers[name] = value;
}

void ModifierBlock::remove_modifier(string name) {
    if (modifiers.find(name) != modifiers.end())
        modifiers.erase(name);
    else
        throw logicblock_error("Can't erase modifier, it dosent exist");
}

LogicBlock* ModifierBlock::execute() {

    cout << "Running block" << endl;

    for (map<string, int>::iterator it = modifiers.begin(); it != modifiers.end(); ++it)
        target->add_to_attribute(it->first, it->second);

    return this->get_next();
}

#include "ModifierBlock.h"
#include "Character.h"

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

QMap<QString, qint8> ModifierBlock::get_modifiers() const {
    return modifiers;
}

void ModifierBlock::set_modifier(QString name, int value) {
    modifiers[name] = value;
}

void ModifierBlock::remove_modifier(QString name) {
    if (modifiers.find(name) != modifiers.end())
        modifiers.remove(name);
    else
        throw logicblock_error("Can't erase modifier, it dosent exist");
}

LogicBlock* ModifierBlock::execute() {

  for (auto key : modifiers.keys()) {
    target->add_to_attribute(key,modifiers.value(key));
  }
    //for (QMap<QString, qint8>::iterator it = modifiers.begin(); it != modifiers.end(); ++it)
     //   target->add_to_attribute(it->first, it->second);

    return this->get_next();
}

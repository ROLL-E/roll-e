#include "ModifierBlock.h"
#include "Character.h"

using namespace std;

ModifierBlock::ModifierBlock(ModifierBlock& other) : LogicBlock(){
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

qint8 ModifierBlock::get_modifier(const QString& name) const {
    return modifiers.value(name);
}

void ModifierBlock::set_modifier(QString name, qint8 value) {
  modifiers[name] = value;
}

void ModifierBlock::set_previous_modifier(ModifierBlock* other) {
    previous_modifier = other;
    target = other->get_target();
    for (QString key : other->modifiers.keys()) {
        set_modifier(key,other->get_modifier(key)*-1);
    }
}

ModifierBlock* ModifierBlock::get_previous_modifer() const {
    return previous_modifier;
}

void ModifierBlock::populate_id_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars) {
  next_id = blocks.indexOf(get_next());
  target_id = chars.indexOf(target);
  previous_mod_id = blocks.indexOf(previous_modifier);
  if (get_next() != nullptr)
    get_next()->populate_id_fields(blocks, chars);
}

void ModifierBlock::populate_pointer_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars) {
  set_next(blocks.value(next_id));
  set_target(chars.value(target_id));
  previous_modifier = dynamic_cast<ModifierBlock*>(blocks.value(previous_mod_id));
  if (get_next() != nullptr) {
    get_next()->populate_pointer_fields(blocks, chars);
  }
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
  return this->get_next();
}

QDataStream& ModifierBlock::write_to_stream(QDataStream & ds) {
  ds << next_id;
  ds << get_last();

  ds << modifiers;
  ds << target_id;
  ds << previous_mod_id;

  return ds;
}

QDataStream& ModifierBlock::read_from_stream(QDataStream& ds) {
  bool temp_last;

  ds >> next_id;
  ds >> temp_last;

  set_last(temp_last);

  ds >> modifiers;
  ds >> target_id;

  ds >> previous_mod_id;

  return ds;
}

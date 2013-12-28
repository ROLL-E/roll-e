#include "scenariocontroller.h"
#include "ValueBlock.h"
#include "CompareBlock.h"
#include "DamageBlock.h"
#include "WaitBlock.h"

#include <QDebug>
#include <QtQml>
#include "qtquick2applicationviewer.h"

ScenarioController::ScenarioController()
{
    current_scenario_ = new Scenario{};
    active_block_number_ = 0;
    active_block_side_ = "null";

    showEditor_ = true;
}

ScenarioController::ScenarioController(Scenario* newScenario)
{
    current_scenario_ = newScenario;
    active_block_number_ = 0;
    active_block_side_ = "null";

    showEditor_ = true;
}

ScenarioController::ScenarioController(Character *primary_character, QList<Character *> all_characters, QMap<quint16, Item*> items,  QList<Skill*> skills, QList<QString> attributes)
{
    current_scenario_ = new Scenario;
    active_block_number_ = 0;
    active_block_side_ = "null";

    primary_character_ = primary_character;
    all_characters_ = all_characters;

    items_ = items;
    skills_ = skills;
    attributes_ = attributes;

    showEditor_ = true;

    update_characters();
    update_items();
    update_skills();
    update_attributes();


}


void ScenarioController::add_block(int number, QString type)
{
    qDebug() << "Adding block to of type " << type << " to scenario and mapping it to " << number;

    LogicBlock* newLogicBlock;

    // make block of correct type
    if(type == "V"){
        newLogicBlock = new ValueBlock{};
    }else if (type == "C"){
        newLogicBlock = new CompareBlock{};
    }else if (type == "D"){
        newLogicBlock = new  DamageBlock{};
    }else if (type == "W"){
        newLogicBlock = new WaitBlock{};
    }

    block_map_[number] = newLogicBlock;

    // if first block in scenario
    if(active_block_number_ == 0 && active_block_side_ == "null"){
        qDebug() << "first block!";

        current_scenario_->set_head(newLogicBlock);
        current_scenario_->set_next_block(newLogicBlock);
    }else {
        // check if alternate slot should be used (for CompareBlock)
        qDebug() << "not first block";
        if(active_block_side_ == "rhs")
        {
            qDebug() << "set alternet side";
            dynamic_cast<CompareBlock*>(block_map_.value(active_block_number_))->set_alternate(newLogicBlock);
        }else {
            block_map_.value(active_block_number_)->set_next(newLogicBlock);
        }

    }

}

void ScenarioController::edit_valueblock(QString stat, bool intent, int blocknr)
{
    qDebug() << "Editing valueblock nr: " << blocknr;

    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_intention((intent ? 'r' : 's'));

    if(!intent){
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_value(stat.toInt());
    }

}

void ScenarioController::edit_compareblock(QString stat, bool intent, int blocknr)
{
    qDebug() << "Editing compareblock nr: " << blocknr;

}

void ScenarioController::edit_damageblock(QString text, bool check, int blocknr)
{
    qDebug() << "Editing damageeblock nr: " << blocknr;
}

void ScenarioController::set_block_value(int blocknr)
{
    qDebug() << "Set input " << active_block_side_ << " to compareblock nr: " << blocknr;

    if(active_block_side_ == "rhs"){
        // set rhs-value in drop target to pointer to relevant valueblock
        qDebug() << "setting rhs";    
        dynamic_cast<CompareBlock*>(block_map_[active_block_number_])->set_rhs(dynamic_cast<ValueBlock*>(block_map_[blocknr]));
    }else if(active_block_side_ == "lhs"){
        qDebug() << "setting rhs";
        dynamic_cast<CompareBlock*>(block_map_[active_block_number_])->set_lhs(dynamic_cast<ValueBlock*>(block_map_[blocknr]));
    }else if (active_block_side_ == "none"){
        qDebug() << "setting Damageblock input";
        dynamic_cast<DamageBlock*>(block_map_[active_block_number_])->set_valueblock(dynamic_cast<ValueBlock*>(block_map_[blocknr]));
    }else{
        qDebug() << "Error in setting compareblock value.";
    }
}


void ScenarioController::set_valueblock_intention(QString intention, int blocknr)
{
    qDebug() << "Setting intention:" << intention;
    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_intention(intention[0]);
    qDebug() << "from block, intention" << dynamic_cast<ValueBlock*>(block_map_[blocknr])->get_intention();
}


void ScenarioController::set_valueblock_value(int value,  int blocknr)
{
    qDebug() << "setting value to " << value << " in block nr."  << blocknr;

    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_value(value);
}

void ScenarioController::set_valueblock_roll(int sides, int number, int blocknr)
{
    qDebug() << sides << number << blocknr;

    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_sides(sides);
    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_number(number);

    qDebug() << "read form block" << dynamic_cast<ValueBlock*>(block_map_[blocknr])->get_sides()
             << dynamic_cast<ValueBlock*>(block_map_[blocknr])->get_number();
}

void ScenarioController::add_attribute_valueblock(QString attribute, int blocknr)
{
    qDebug() << "Attribute, add" << attribute << blocknr;

    try {
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->add_to_attributes(attribute);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }

    qDebug() << "read form block" << dynamic_cast<ValueBlock*>(block_map_[blocknr])->get_attributes();
}

void ScenarioController::remove_attribute_valueblock(QString attribute, int blocknr)
{
    qDebug() << "Attribute, remove" << attribute << blocknr;

    try {
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->remove_attribute(attribute);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }

    qDebug() << "read form block" << dynamic_cast<ValueBlock*>(block_map_[blocknr])->get_attributes();
}

void ScenarioController::add_skill_valueblock(int skill, QString modifier, int blocknr)
{
    qDebug() << "Skill, add" << skill << blocknr;

    try {

        dynamic_cast<ValueBlock*>(block_map_[blocknr])->add_to_applicable_skills(skill_map_[skill], modifier);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }

    qDebug() << "read form block" << dynamic_cast<ValueBlock*>(block_map_[blocknr])->get_applicable_skills();
}

void ScenarioController::remove_skill_valueblock(int skill, int blocknr)
{
    qDebug() << "Skill, remove" << skill << blocknr;

    try {
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->remove_applicable_skill(skill_map_[skill]);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }

    qDebug() << "read form block" << dynamic_cast<ValueBlock*>(block_map_[blocknr])->get_applicable_skills();

}
void ScenarioController::add_item_valueblock(int id, QString attribute, int blocknr)
{
    qDebug() << "Item, add" << id << blocknr;

    try {
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->add_to_applicable_items(id, attribute);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }

    qDebug() << "read form block" << dynamic_cast<ValueBlock*>(block_map_[blocknr])->get_applicable_items();
}

void ScenarioController::remove_item_valueblock(QString item, int id, int blocknr)
{
    qDebug() << "Item, remove" << item << blocknr;

    try {
        // does not make sense... int as key? WHY?
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->remove_applicable_item(id);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }

     qDebug() << "read form block" << dynamic_cast<ValueBlock*>(block_map_[blocknr])->get_applicable_items();

}

void ScenarioController::set_damegeblock_target(QString character, int blocknr)
{
    qDebug() << "setting damageblock " << blocknr << "s target to character" << character;

    dynamic_cast<DamageBlock*>(block_map_[blocknr])->set_target(character_map_[character]);

    qDebug() << "read form block" << dynamic_cast<DamageBlock*>(block_map_[blocknr])->get_target()
             << "with name" << dynamic_cast<DamageBlock*>(block_map_[blocknr])->get_target()->get_name() ;
}


void ScenarioController::update_characters()
{
    qDebug() << "Updating Characters";

    character_list_.clear();
    character_map_.clear();

    for(Character* character : all_characters_) {
        character_list_.append(character->get_name());
        character_map_[character->get_name()] = character;
    }

    emit character_list_changed();

    qDebug() << "Stringlist:" << character_list_ << "Map:" << character_map_;
    return;
}

void ScenarioController::update_items()
{
    qDebug() << "Updating Items";

    item_model_.clear();
    for (Item* item: items_) {

            for (auto attribute : item->get_attributes().keys())
            {
                qDebug() << "adding" << item->get_name() << attribute;
                item_model_.append(new ItemModel{item->get_name(), attribute, item->get_id()});

            }
    }
    emit itemsChanged();
    qDebug() << items_;
    qDebug() << "update item, from model:" << item_model_;


}

void ScenarioController::update_skills()
{
    qDebug() << "Updating Skills";

    skill_map_.clear();
    skill_model_.clear();

    int i{0};
    for (Skill* skill: skills_) {
        skill_map_[i] = skill;
        qDebug() << "setting:" << skill << "to mapnr" << i;
        for (auto modifier: skill->get_modifiers().keys())
        {
            qDebug() << "adding" << skill->get_name() << modifier;
            skill_model_.append(new SkillModel{skill->get_name(), modifier, i});
        }
        i++;
    }
    emit skillsChanged();

    qDebug() << "skill map:" << skill_map_;
}

void ScenarioController::update_attributes()
{
    qDebug() << "Updating Attributes";

    attribute_model_.clear();
    for(auto attribute: attributes_) {
        attribute_model_.append(attribute);
    }

    qDebug() << "Model:" << attribute_model_;
}

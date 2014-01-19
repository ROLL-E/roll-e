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

    LogicBlock* newLogicBlock;

    // make block of correct type
    if(type == "V"){
        ValueBlock *tempblock;
        tempblock = new ValueBlock{};
        tempblock->set_target(primary_character_);
        newLogicBlock = tempblock;
    }else if (type == "C"){
        newLogicBlock = new CompareBlock{};
    }else if (type == "D"){
        DamageBlock *tempblock;
        tempblock = new DamageBlock();
        tempblock->set_target(primary_character_);
        newLogicBlock = tempblock;

    }else if (type == "W"){
        newLogicBlock = new WaitBlock{};
    }

    block_map_[number] = newLogicBlock;

    // if first block in scenario
    if(active_block_number_ == 0 && active_block_side_ == "null"){

        current_scenario_->set_head(newLogicBlock);
        current_scenario_->set_next_block(newLogicBlock);
    }else {
        // check if alternate slot should be used (for CompareBlock)
        if(active_block_side_ == "rhs")
        {
            dynamic_cast<CompareBlock*>(block_map_.value(active_block_number_))->set_alternate(newLogicBlock);
        }else {
            block_map_.value(active_block_number_)->set_next(newLogicBlock);
        }

    }

}

void ScenarioController::edit_valueblock(QString stat, bool intent, int blocknr)
{

    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_intention((intent ? 'r' : 's'));

    if(!intent){
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_value(stat.toInt());
    }

}


void ScenarioController::set_block_value(int blocknr)
{

    if(active_block_side_ == "rhs"){
        // set rhs-value in drop target to pointer to relevant valueblock
        dynamic_cast<CompareBlock*>(block_map_[active_block_number_])->set_rhs(dynamic_cast<ValueBlock*>(block_map_[blocknr]));
    }else if(active_block_side_ == "lhs"){
        dynamic_cast<CompareBlock*>(block_map_[active_block_number_])->set_lhs(dynamic_cast<ValueBlock*>(block_map_[blocknr]));
    }else if (active_block_side_ == "none"){

        dynamic_cast<DamageBlock*>(block_map_[active_block_number_])->set_valueblock(dynamic_cast<ValueBlock*>(block_map_[blocknr]));
    }else{

    }
}


void ScenarioController::set_valueblock_intention(QString intention, int blocknr)
{
    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_intention(intention[0]);
}


void ScenarioController::set_valueblock_value(int value,  int blocknr)
{
    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_value(value);
}

void ScenarioController::set_valueblock_roll(int sides, int number, int blocknr)
{

    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_sides(sides);
    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_number(number);
}

void ScenarioController::add_attribute_valueblock(QString attribute, int blocknr)
{

    try {
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->add_to_attributes(attribute);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }

}

void ScenarioController::remove_attribute_valueblock(QString attribute, int blocknr)
{
    try {
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->remove_attribute(attribute);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }


}

void ScenarioController::add_skill_valueblock(int skill, QString modifier, int blocknr)
{
    try {

        dynamic_cast<ValueBlock*>(block_map_[blocknr])->add_to_applicable_skills(skill_map_[skill], modifier);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }


}

void ScenarioController::remove_skill_valueblock(int skill,QString attribute,  int blocknr)
{
    try {
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->remove_applicable_skill(skill_map_[skill], attribute);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }

}
void ScenarioController::add_item_valueblock(int id, QString attribute, int blocknr)
{
    try {
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->add_to_applicable_items(id, attribute);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }
}

void ScenarioController::remove_item_valueblock(QString item, QString modifier,  int id, int blocknr)
{
    try {
        // does not make sense... int as key? WHY?
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->remove_applicable_item(id, modifier);
    }catch (logicblock_error e) {
        qDebug() << e.what();
    }
}

void ScenarioController::set_valueblock_target(QString character, int blocknr)
{
    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_target(character_map_[character]);
}

void ScenarioController::set_damegeblock_target(QString character, int blocknr)
{
    dynamic_cast<DamageBlock*>(block_map_[blocknr])->set_target(character_map_[character]);
}


void ScenarioController::update_characters()
{
    character_list_.clear();
    character_map_.clear();

    for(Character* character : all_characters_) {
        character_list_.append(character->get_name());
        character_map_[character->get_name()] = character;
    }

    emit character_list_changed();

    return;
}

void ScenarioController::update_items()
{
    item_model_.clear();
    for (Item* item: items_) {

            for (auto attribute : item->get_attributes().keys())
            {
                item_model_.append(new ItemModel{item->get_name(), attribute, item->get_id()});
            }
    }
    emit itemsChanged();
}

void ScenarioController::update_skills()
{
    skill_map_.clear();
    skill_model_.clear();

    int i{0};
    for (Skill* skill: skills_) {
        skill_map_[i] = skill;
        for (auto modifier: skill->get_modifiers().keys())
        {
            skill_model_.append(new SkillModelQML{skill->get_name(), modifier, i});
        }
        i++;
    }
    emit skillsChanged();
}

void ScenarioController::update_attributes()
{
    attribute_model_.clear();
    for(auto attribute: attributes_) {
        attribute_model_.append(attribute);
    }
}

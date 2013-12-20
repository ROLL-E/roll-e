#include "scenariocontroller.h"
#include "scenario.h"
#include "ValueBlock.h"
#include "CompareBlock.h"
#include "DamageBlock.h"
#include "WaitBlock.h"

#include <QDebug>

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

void ScenarioController::add_block(int number, QString type){
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

    //

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

void ScenarioController::edit_valueblock(QString stat, bool intent, int blocknr) {
    qDebug() << "Editing valueblock nr: " << blocknr;

    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_intention((intent ? 'r' : 's'));

    if(!intent){
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_value(stat.toInt());
    }

}

void ScenarioController::edit_compareblock(QString stat, bool intent, int blocknr) {
    qDebug() << "Editing compareblock nr: " << blocknr;

}

void ScenarioController::edit_damageblock(QString text, bool check, int blocknr) {
    qDebug() << "Editing damageeblock nr: " << blocknr;
}

void ScenarioController::set_compareblock_value(int blocknr){
    qDebug() << "Set input " << active_block_side_ << " to compareblock nr: " << blocknr;

    if(active_block_side_ == "rhs"){
        // set rhs-value in drop target to pointer to relevant valueblock
        qDebug() << "setting rhs";
        dynamic_cast<CompareBlock*>(block_map_[active_block_number_])->set_rhs(dynamic_cast<ValueBlock*>(block_map_[blocknr]));
    }else if(active_block_side_ == "lhs"){
        qDebug() << "setting rhs";
        dynamic_cast<CompareBlock*>(block_map_[active_block_number_])->set_lhs(dynamic_cast<ValueBlock*>(block_map_[blocknr]));
    }else{
        qDebug() << "Error in setting compareblock value.";
    }
}

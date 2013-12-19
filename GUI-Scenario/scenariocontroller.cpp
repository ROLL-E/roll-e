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
    LogicBlock* newLogicBlock;

    if(type == "V"){
        newLogicBlock = new ValueBlock{};
    }else if (type == "C"){
        newLogicBlock = new CompareBlock{};
    }else if (type == "C"){
        newLogicBlock = new  DamageBlock{};
    }else if (type == "C"){
        newLogicBlock = new WaitBlock{};
    }

    block_map_[number] = newLogicBlock;

    // if first block
    if(active_block_number_ == 0 && active_block_side_ == "null"){

        current_scenario_->set_head(newLogicBlock);
        current_scenario_->set_next_block(newLogicBlock);
    }else {
        // if not first

        // check if alternate slot
        if(active_block_side_ == "rhs")
        {
            dynamic_cast<CompareBlock*>(block_map_.value(active_block_number_))->set_alternate(newLogicBlock);
        }else {
            block_map_.value(active_block_number_)->set_next(newLogicBlock);
        }

    }

}

void ScenarioController::edit_value_block(QString stat, bool intent, int blocknr) {
    dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_intention((intent ? 'r' : 's'));

    if(!intent){
        dynamic_cast<ValueBlock*>(block_map_[blocknr])->set_value(stat.toInt());
    }

}

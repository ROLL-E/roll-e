#include "WaitBlock.h"

void WaitBlock::set_wait_turns(int new_number) {
    wait_turns = new_number;
}

int WaitBlock::get_wait_turns() const {
    return wait_turns;
}

LogicBlock* WaitBlock::execute() {

    if (wait_counter == wait_turns)
        return this->get_next();
    else
        wait_counter++;
    return this;
}

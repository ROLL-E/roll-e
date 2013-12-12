#ifndef SCENARIO_H
#define SCENARIO_H
#include "LogicBlock.h"
#include "WaitBlock.h"
#include <map>
#include <string>

class Scenario {

private:
    std::map<std::string, bool> current_flags;
    LogicBlock* head;
    LogicBlock* next_block;

public:
    Scenario() = default;
    Scenario(Scenario&);
    void run();
    void wait_turns(int);
    int find_turn_depth() const;
    void set_flag(const std::string&, bool);
    std::map<std::string,bool> get_flags() const;
    bool get_flag(const std::string&) const;
    void set_head(LogicBlock*);
    LogicBlock* get_head() const;

};

#endif

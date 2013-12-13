#ifndef SCENARIO_H
#define SCENARIO_H
#include <map>
#include <string>

class LogicBlock;

class Scenario {

private:
    std::map<std::string, bool> current_flags;
    LogicBlock* head;
    LogicBlock* next_block;

public:
    Scenario() = default;
    Scenario(Scenario&);
    void run();
    void wait_turns(int) const;
    int find_turn_depth() const;
    void set_flag(std::string, bool);
    std::map<std::string,bool> get_flags();
    bool get_flag(std::string);
    void set_head(LogicBlock*);

};

#endif

#ifndef RULESET_H
#define RULESET_H
#include <list>
#include <string>
#include "Skill.h"
#include "Scenario.h"

class Ruleset {

private:
    std::list<std::string> allowed_attributes;
    std::list<Skill*> allowed_skills;
    std::list<Scenario*> scenarios;

public:
    Ruleset(std::list<std::string>);
    std::list<Scenario*> get_scenarios() const;
    void add_scenario(Scenario*);
    void remove_scenario(Scenario*);
    void add_skill(Skill*);
    void remove_skill(Skill*);
};

#endif

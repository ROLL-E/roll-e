#include "Ruleset.h"

using namespace std;

Ruleset::Ruleset(std::list<string> attributes)
  : allowed_attributes{attributes} {
}

Ruleset::Ruleset(const Ruleset& other)
  : allowed_attributes{other.allowed_attributes},
    allowed_skills{other.allowed_skills},
    scenarios{other.scenarios} {

}

list<Scenario*> Ruleset::get_scenarios() const {
  return scenarios;
}

void Ruleset::add_scenario(Scenario* new_scenario) {
  scenarios.push_back(new_scenario);
}

void Ruleset::add_skill(Skill* new_skill) {
  allowed_skills.push_back(new_skill);
}

void Ruleset::remove_scenario(Scenario* scen_to_remove) {
  scenarios.remove(scen_to_remove);
}

void Ruleset::remove_skill(Skill* skill_to_remove) {
  allowed_skills.remove(skill_to_remove);
}





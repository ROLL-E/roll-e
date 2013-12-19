#include "Ruleset.h"

using namespace std;

Ruleset::Ruleset(QList<QString> attributes)
  : allowed_attributes{attributes} {
}

Ruleset::Ruleset(const Ruleset *other)
  : allowed_attributes{other->allowed_attributes},
    allowed_skills{other->allowed_skills},
    scenarios{other->scenarios} {

}

QList<Scenario*> Ruleset::get_scenarios() const {
  return scenarios;
}

QList<Skill *> &Ruleset::get_skills() {
  return allowed_skills;
}

QList<QString> Ruleset::get_attributes() const {
  return allowed_attributes;
}

void Ruleset::add_scenario(Scenario* new_scenario) {
  scenarios.push_back(new_scenario);
}

void Ruleset::add_skill(Skill* new_skill) {
  allowed_skills.push_back(new_skill);
}

void Ruleset::remove_scenario(Scenario* scen_to_remove) {
  scenarios.removeOne(scen_to_remove);
}

void Ruleset::remove_skill(Skill* skill_to_remove) {
  allowed_skills.removeOne(skill_to_remove);
}





#ifndef ACTIVESKILL_H
#define ACTIVESKILL_H
#include "Skill.h"
#include <string>

class ActiveSkill : public Skill
{
private:
  Scenario* scenario;
public:
  ActiveSkill(std::string);
  Scenario* get_scenario() const;
  void set_scenario(Scenario*);
  void activate() const;
};

#endif
#ifndef SKILL_H
#define SKILL_H
#include <string>
#include <map>

class Skill
{
  private:
  std::map<std::string,int> modifiers;
  std::string name;

  public:
  Skill(std::string);
  std::map<std::string,int> get_modifiers() const;
  void set_modifier(std::string, int);
  void remove_modifier(std::string);
  std::string get_name() const;
  void set_name(std::string);

};
#endif

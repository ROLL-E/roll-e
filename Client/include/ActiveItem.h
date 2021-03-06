#ifndef ACTIVEITEM_H
#define ACTIVEITEM_H
#include "Item.h"
#include <string>

class Scenario;
class ActiveItem : public Item
{
private:
  Scenario* scenario;

public:
  ActiveItem(std::string);
  Scenario* get_scenaio() const;
  void set_scenario(Scenario*);
  void activate() const;
};

#endif

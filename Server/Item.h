#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>
#inculde "Story.h"

class Item
{
private:
  std::string name;
  std::map<std::string, int> modifiers;
  int ID;
  std::map<std::string, int> attributes;

public:
  Item(std::string);
	Item(Item&);
	std::string get_name() const;
	void set_name(std::string)
	std::map<std::string,int> get_modifiers() const;
	void set_modifier(std::string,int);
	void remove_modifier(std::string);
	int get_id() const;
	void set_id(int);
	std::map<std::string,int> get_attributes() const;
	void set_attribute(std::string, int);
  void remove_attrubute(std::string)
};

#endif
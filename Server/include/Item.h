#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>

class Item
{
private:
  std::string name;
  std::map<std::string, int> modifiers;
  int ID;
  std::map<std::string, int> attributes;
  int weight;

  static int next_ID; // ID that the next item should be assigned

public:
  Item(const std::string&);
  Item(const Item&);

  std::string get_name() const;
  std::map<std::string,int> get_modifiers() const;
  int get_id() const;
  std::map<std::string,int> get_attributes() const;
  int get_weight() const;

  void set_name(const std::string&);
  void set_modifier(const std::string&,int);
  void set_id(int); //shouldn't really be allowed to change
  void set_attribute(const std::string&, int);
  void set_weight(int);

  void remove_modifier(const std::string&);
  void remove_attribute(const std::string&);
};

#endif

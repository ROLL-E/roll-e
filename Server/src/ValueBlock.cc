#include "ValueBlock.h"

using namespace std;

void ValueBlock::set_intention(char new_intention) {
    intention = new_intention;
}

char ValueBlock::get_intention() const {
    return intention;
}

void ValueBlock::set_value(int new_value) {
    value = new_value;
}

int ValueBlock::get_value() const {
    return value;
}

void ValueBlock::set_sides(int new_sides) {
    sides = new_sides;
}

int ValueBlock::get_sides() const {
    return sides;
}

void ValueBlock::set_number(int new_number) {
    number = new_number;
}

int ValueBlock::get_number() const {
    return number;
}

void ValueBlock::set_target(Character* new_target) {
    target = new_target;
}

Character* ValueBlock::get_target() const {
    return target;
}

list<string> ValueBlock::get_attributes() const {
    return attributes;
}

void ValueBlock::add_to_attributes(const string& new_attribute) {
    list<string>::iterator it;
    it = find(attributes.begin(), attributes.end(), new_attribute);
    if (it == attributes.end())
        attributes.push_front(new_attribute);
    else
        throw logicblock_error("Attribute already exists");
}

void ValueBlock::remove_attribute(const string& attribute) {
    list<string>::iterator it;
    it = find(attributes.begin(), attributes.end(), attribute);
    if (it != attributes.end())
        attributes.erase(it);
    else
        throw logicblock_error("Can't remove attriubte, it doesn't exist in the list");
}

list<string> ValueBlock::get_applicable_skills() const {
    return applicable_skills;
}

void ValueBlock::add_to_applicable_skills(const string& name) {
    list<string>::iterator it;
    it = find(applicable_skills.begin(), applicable_skills.end(), name);
    if ( it == applicable_skills.end())
        applicable_skills.push_back(name);
    else
        throw logicblock_error("Skill already exsists");
}

void ValueBlock::remove_applicable_skill(const string& name) {
    list<string>::iterator it;
    it = find(applicable_skills.begin(), applicable_skills.end(), name);
    if (it != applicable_skills.end())
        applicable_skills.erase(it);
    else
        throw logicblock_error("Can't remove skill, it doesn't exist in list");
}

list<int> ValueBlock::get_applicable_items() const {
    return applicable_items;
}

void ValueBlock::add_to_applicable_items(int id) {
    list<int>::iterator it;
    it = find(applicable_items.begin(), applicable_items.end(), id);
    if (it == applicable_items.end())
        applicable_items.push_back(id);
    else
        throw logicblock_error("Item alredy exists");
}

void ValueBlock::remove_applicable_item(int id) {
    list<int>::iterator it;
    it = find(applicable_items.begin(), applicable_items.end(), id);
    if (it != applicable_items.end())
        applicable_items.erase(it);
    else
        throw logicblock_error("Can't remove item, it doesn't exist in list");
}

map<string, bool> ValueBlock::get_flags() const {
    return flags;
}

void ValueBlock::set_flag(const string& name, bool value) {
    flags[name] = value;
}

void ValueBlock::remove_flag(const string& name) {
    map<string,bool>::iterator it;
    it = flags.find(name);
    if (it != flags.end())
        flags.erase(it);
    else
        throw logicblock_error("Can't remove flag, it doesn't exist");
}

int ValueBlock::roll() const {
    int temp{0};
    srand(time(NULL));
    for (int i{0}; i < number ; ++i)
        temp += (rand() % sides) + 1;
    return temp;
}


LogicBlock* ValueBlock::execute() {
    if (intention == 's')
        return this->get_next();
    else if (intention == 'r') {
        value = roll();
    }
    else if (intention == 'a') {
        list<string>::iterator it;
        for (it = attributes.begin(); it != attributes.end(); ++it)
            value += target->get_attribute(*it);
        value += roll();
    }
    return this->get_next(); //Not yet implemented
}

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

void ValueBlock::add_to_attributes(string new_attribute) {
    list<string>::iterator it;
    it = find(attributes.begin(), attributes.end(), new_attribute);
    if (it == attributes.end())
        attributes.push_front(new_attribute);
    else
        throw logicblock_error("Attribute already exists");
}

void ValueBlock::remove_attribute(string attribute) {
    list<string>::iterator it;
    it = find(attributes.begin(), attributes.end(), attribute);
    if (it != attributes.end())
        attributes.erase(it);
    else
        throw logicblock_error("Can't remove attriubte, it dosen't exist in the list");
}

LogicBlock* ValueBlock::execute() {
    return this->get_next();
}

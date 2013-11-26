#ifndef INVENTORY_H
#define INVENTORY_H
#include <list>

class Inventory {
private:
    std::list<int> items;
    int max_weight;
    int current_weight;
    std::list<int> equipped;

public:
    Inventory(int);
    Inventory(Inventory&);
    void add_item(int);
    void remove_item(int);
    bool has_item(int);
    void set_max_weight(int);
    int get_weight() const;
    int get_max_weight() const;
    std::list<int> get_equipped() const;
    void equip(int);
    void unequip(int);
};

#endif

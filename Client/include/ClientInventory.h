#ifndef CLIENTINVENTORY_H
#define CLIENTINVENTORY_H
#include <list>

class ClientInventory {
private:
    std::list<Item*> items;
    int max_weight;
    int current_weight;
    std::list<Item*> equipped;

public:
    ClientInventory(int);
    ClientInventory(ClientInventory& other) {};
    void add_item(int);
    void remove_item(int);
    bool has_item(int) const;
    void set_max_weight(int);
    int get_weight() const;
    int get_max_weight() const;
    std::list<Item*> get_equipped() const;
    void equip(int);
    void unequip(int);
};

#endif

#ifndef CLIENTINVENTORY_H
#define CLIENTINVENTORY_H
#include <QList>

class Item;

class ClientInventory {
private:
    QList<Item*> items;
    int max_weight;
    int current_weight;
    QList<Item*> equipped;

public:
    ClientInventory(int);
    ClientInventory(const ClientInventory&);
    void add_item(Item*);
    void remove_item(Item*);
    bool has_item(Item*) const;
    void set_max_weight(Item*);
    int get_weight() const;
    int get_max_weight() const;
    void set_max_weight(int);
    QList<Item*> get_equipped() const;
    void equip(Item*);
    void unequip(Item*);
};

#endif

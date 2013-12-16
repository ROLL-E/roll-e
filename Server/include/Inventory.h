#ifndef INVENTORY_H
#define INVENTORY_H
#include <QList>

class Inventory {
private:
    QList<int> items;
    int max_weight;
    int current_weight;
    QList<int> equipped;

public:
    Inventory(int);
    Inventory(const Inventory&);

    int get_weight() const;
    int get_max_weight() const;
    QList<int> get_equipped() const;
    QList<int> get_items() const;
    bool has_item(int) const;

    void set_max_weight(int);

    void add_item(int);
    void remove_item(int);

    void equip(int);
    void unequip(int);
};

#endif

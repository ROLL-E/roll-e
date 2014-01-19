#ifndef CLIENTINVENTORY_H
#define CLIENTINVENTORY_H
#include <QList>

class Item;

class ClientInventory {
private:
    QList<Item*> items;
    quint16 max_weight;
    quint16 current_weight;
    QList<Item*> equipped;

public:
    ClientInventory(quint16);
    ClientInventory(const ClientInventory&);
    QList<Item*> get_items();
    void add_item(Item*);
    void remove_item(Item*);
    bool has_item(Item*) const;
    void set_max_weight(Item*);
    quint16 get_weight() const;
    quint16 get_max_weight() const;
    void set_max_weight(quint16);
    QList<Item*> get_equipped() const;
    void equip(Item*);
    void unequip(Item*);

    QDataStream& read_from_stream(QDataStream&);

};

  QDataStream& operator>>(QDataStream&, ClientInventory&);


#endif

#ifndef INVENTORY_H
#define INVENTORY_H
#include <QList>
#include <QDataStream>

class Story;

class Inventory {
private:
    QList<quint16> items;
    quint16 max_weight;
    quint16 current_weight;
    QList<quint16> equipped;
    Story* story;

public:
    Inventory(quint16, Story*);
    Inventory(const Inventory&);
    Inventory() {}

    quint16 get_weight() const;
    quint16 get_max_weight() const;
    QList<quint16> get_equipped() const;
    QList<quint16> get_items() const;
    bool has_item(quint16) const;
    void set_max_weight(quint16);

    void add_item(quint16);
    void remove_item(quint16);

    void equip(quint16);
    void unequip(quint16);

    QDataStream& write_to_stream(QDataStream&) const;
    QDataStream& read_from_stream(QDataStream&);
};

QDataStream& operator<<(QDataStream&, Inventory&);
QDataStream& operator>>(QDataStream&, Inventory&);

#endif

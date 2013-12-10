#ifndef INVENTORY_H
#define INVENTORY_H
#include <QList>
#include <QDataStream>


class Inventory {
private:
    QList<quint16> items;
    quint16 max_weight;
    quint16 current_weight;
    QList<quint16> equipped;

public:
    Inventory(quint16);
    Inventory(const Inventory&);

    quint16 get_weight() const;
    quint16 get_max_weight() const;
    QList<quint16> get_equipped() const;
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

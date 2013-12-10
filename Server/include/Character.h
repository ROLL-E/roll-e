#ifndef CHARACTER_H
#define CHARACTER_H
#include <QString>
#include <QMap>
#include <list>
#include <QDataStream>
#include "Skill.h"
#include "ClientConnection.h"
#include "Inventory.h"

class Character {
private:
    QString name;
    ClientConnection* client;
    QMap<QString, qint16> attributes;
    QList<quint16> skills;


public:
    Inventory inventory;
    Character(QMap<QString, qint16>, quint16);
    Character(const Character&);
    QString get_name() const;
    void set_name(const QString&);
    qint16 get_attribute(QString) const;
    void set_attribute(const QString&, qint16);
    void take_damage(const QString&, qint16);
    QList<quint16> get_skills() const;
    void add_skill(quint16);
    void remove_skill(quint16);
    void add_item(quint16);
    void remove_item(quint16);
    bool has_item(quint16) const;

    QDataStream& write_to_stream(QDataStream&);
    QDataStream& read_from_stream(QDataStream&);
};

QDataStream& operator<<(QDataStream&, Character*&);
QDataStream& operator>>(QDataStream&, Character*&);
#endif

#ifndef CHARACTER_H
#define CHARACTER_H
#include <QString>
#include <QMap>
#include <QList>
#include <QDataStream>
#include "Inventory.h"
#include "ClientConnection.h"


class Story;
class Skill;

class Character : public QObject {
    Q_OBJECT
private:
    QString name;

    QPointer<ClientConnection> client;

    QMap<QString, qint16> attributes;
    QList<Skill*> skills;
    Story* story;

public:
    QList<quint16> skill_ids;

    Inventory inventory;
    Character(QMap<QString, qint16>, quint16, Story*);
    Character(const Character&, QObject* parent = 0);
    Character() {}

    QString get_name() const;
    void set_name(const QString&);
    qint16 get_attribute(QString) const;
    QMap<QString, qint16> get_attributes() const;
    void set_attribute(const QString&, qint16);
    void take_damage(const QString&, qint16);
    QList<Skill*> get_skills() const;
    QPointer<ClientConnection> get_connection();
    void set_connection(ClientConnection*);
    void set_story(Story*);

    void add_to_attribute(const QString&, qint16);

    
    void add_skill(Skill*);
    void remove_skill(Skill*);
    void add_item(quint16);
    void remove_item(quint16);
    bool has_item(quint16) const;

    QDataStream& write_to_stream(QDataStream&);
    QDataStream& read_from_stream(QDataStream&);

public slots:
    void reset_connection();
signals:
    void changed(Character*);
};

QDataStream& operator<<(QDataStream&, Character*&);
QDataStream& operator>>(QDataStream&, Character*&);

#endif

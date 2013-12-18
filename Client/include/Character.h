#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QList>
#include <QMap>

#include "Skill.h"
#include "Item.h"
#include "ServerConnection.h"
#include "ClientInventory.h"

class Character {
public:
  Character(QMap<QString,qint16>, quint16);
  Character(const Character&);
  
  QString get_name() const;
  void set_name(const QString&);
  qint16 get_attribute(const QString&) const;
  void set_attribute(const QString&, qint16);
  void add_to_attribute(const QString&, qint16);
  QList<Skill*> get_skills() const;
  void add_skill(Skill*);
  void remove_skill(Skill*);
  void add_item(Item*);
  void remove_item(Item*);
  bool has_item(Item*) const;

  QDataStream& read_from_stream(QDataStream&);
  
private:
  QString name;
  QMap<QString, qint16> attributes;
  QList<Skill*> skills;
  ClientInventory inventory;
  
};

QDataStream& operator>>(QDataStream&, Character*&);

#endif

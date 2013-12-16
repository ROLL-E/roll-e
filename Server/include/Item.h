#ifndef ITEM_H
#define ITEM_H
#include <QMap>
#include <QString>
#include <QDataStream>

class Item
{
private:
  QString name;
  QMap<QString, int> modifiers;
  int ID;
  QMap<QString, int> attributes;
  int weight;

  static int next_ID; // ID that the next item should be assigned

public:
  static void set_next_ID(int);

  Item(const QString&);
  Item(const Item&);
  Item(const quint16&);

  QString get_name() const;
  QMap<QString,int> get_modifiers() const;
  int get_id() const;
  QMap<QString,int> get_attributes() const;
  int get_weight() const;

  void set_name(const QString&);
  void set_modifier(const QString&,int);
  void set_id(int); //shouldn't really be allowed to change
  void set_attribute(const QString&, int);
  void set_weight(int);

  void remove_modifier(const QString&);
  void remove_attribute(const QString&);

  QDataStream& read(QDataStream&);
  QDataStream& write(QDataStream&) const;
};

QDataStream& operator<<(QDataStream&, const Item*&);
QDataStream& operator>>(QDataStream&, Item*&);

#endif

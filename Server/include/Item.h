#ifndef ITEM_H
#define ITEM_H
#include <QMap>
#include <QString>
#include <QDataStream>

class Item
{
private:
  QString name;
  QMap<QString, qint8> modifiers;
  quint16 ID;
  QMap<QString, qint16> attributes;

  static quint16 next_ID; // ID that the next item should be assigned

public:
  static void set_next_ID(quint16);

  Item(const QString&);
  Item(const Item&);
  Item(const quint16&);

  QString get_name() const;
  QMap<QString,qint8> get_modifiers() const;
  quint16 get_id() const;
  QMap<QString,qint16> get_attributes() const;

  void set_name(const QString&);
  void set_modifier(const QString&,qint8);
  void set_id(int); //shouldn't really be allowed to change
  void set_attribute(const QString&, qint16);

  void remove_modifier(const QString&);
  void remove_attribute(const QString&);

  QDataStream& read_from_stream(QDataStream&);
  QDataStream& write_to_stream(QDataStream&) const;
};

QDataStream& operator<<(QDataStream&, Item*&);
QDataStream& operator>>(QDataStream&, Item*&);

#endif

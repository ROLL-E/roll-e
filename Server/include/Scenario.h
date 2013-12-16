#ifndef SCENARIO_H
#define SCENARIO_H

#include "LogicBlock.h"
#include <QMap>
#include <QString>
#include <QDataStream>

class LogicBlock;

class Scenario {

private:
  QString description;
  QMap<QString, bool> current_flags;
  LogicBlock* head;
  LogicBlock* next_block;

public:
  quint16 head_id;
  quint16 next_block_id;

  Scenario() = default;
  Scenario(Scenario&);
  void run();
  void wait_turns(int);
  int find_turn_depth() const;
  void set_flag(const QString&, bool);
  QMap<QString,bool> get_flags() const;
  bool get_flag(const QString&) const;
  void set_head(LogicBlock*);
  LogicBlock* get_head() const;
  void set_next_block(LogicBlock*);
  LogicBlock* get_next_block() const;

  QDataStream& write_to_stream(QDataStream&);
  QDataStream& read_from_stream(QDataStream&);
};

QDataStream& operator<<(QDataStream&, Scenario*);
QDataStream& operator>>(QDataStream&, Scenario*);

#endif

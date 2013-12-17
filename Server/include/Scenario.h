#ifndef SCENARIO_H
#define SCENARIO_H

#include <QMap>
#include <QString>
#include <QDataStream>

class LogicBlock;
class Story;

class Scenario {

private:
  QString description;
  QMap<QString, bool> current_flags;
  LogicBlock* head;
  LogicBlock* next_block;
  Story* parent_story{nullptr};


public:
  quint16 head_id;
  quint16 next_block_id;
  QList<LogicBlock*> all_blocks;

  Scenario() = default;
  Scenario(Scenario&);
  ~Scenario() {delete head;};

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
  void set_story(Story*);

  QDataStream& write_to_stream(QDataStream&);
  QDataStream& read_from_stream(QDataStream&);
};

QDataStream& operator<<(QDataStream&, Scenario*&);
QDataStream& operator>>(QDataStream&, Scenario*&);

#endif

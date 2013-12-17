#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H
#include <stdexcept>
#include <QDataStream>

class Character;

class logicblock_error : public std::logic_error
{
public:
    explicit logicblock_error(const std::string& arg) noexcept
        : std::logic_error(arg) {}
};

class LogicBlock
{
private:
  LogicBlock* next{nullptr};
  bool last_block{false};
public:
  quint16 next_id;

  LogicBlock() = default;
  LogicBlock(LogicBlock&);
  virtual ~LogicBlock() {delete next;};

  virtual LogicBlock* execute() = 0;
  virtual QDataStream& write_to_stream(QDataStream&) = 0;
  virtual QDataStream& read_from_stream(QDataStream&) = 0;

  void add_to_list(QList<LogicBlock*>&); // recursively adds the block to a list of pointers
  virtual void populate_id_fields(QList<LogicBlock*>&, QList<Character*>&) = 0; // recursively sets the correct ids from the indexes of the block and character lists
  virtual void populate_pointer_fields(QList<LogicBlock*>&, QList<Character*>&) = 0; // does the reverse of the above

  void set_next(LogicBlock*);
  LogicBlock* get_next();
  void set_last(bool);
  bool get_last() const;
  LogicBlock* get_self();
};

QDataStream& operator<<(QDataStream& ds, LogicBlock*& block);

QDataStream& operator>>(QDataStream& ds, LogicBlock*& block);

#endif

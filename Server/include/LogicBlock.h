#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H
#include <stdexcept>
#include <QDataStream>

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
  LogicBlock() = default;
  LogicBlock(LogicBlock&);

  virtual LogicBlock* execute() = 0;
  virtual QDataStream& write_to_stream(QDataStream&) = 0;
  virtual QDataStream& read_from_stream(QDataStream&) = 0;

  void set_next(LogicBlock*);
  LogicBlock* get_next();
  void set_last(bool);
  bool get_last() const;
  LogicBlock* get_self();
};

QDataStream& operator<<(QDataStream& ds, LogicBlock*& block);

QDataStream& operator>>(QDataStream& ds, LogicBlock*& block);

#endif

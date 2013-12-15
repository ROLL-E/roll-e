#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H
#include <stdexcept>

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
  void set_next(LogicBlock*);
  LogicBlock* get_next();
  void set_last(bool);
  bool get_last() const;
  LogicBlock* get_self();
};

#endif

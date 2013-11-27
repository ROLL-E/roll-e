#include "serverwindow.h"
#include <QApplication>
#include <iostream>
#include "LogicBlock.h"
#include "ModifierBlock.h"
#include "WaitBlock.h"

using namespace std;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ServerWindow w;

  WaitBlock* block1(new WaitBlock);

  LogicBlock* next_block;

  block1->set_wait_turns(2);
  next_block = block1;

  do {
      cout << "väntar" << endl;
      next_block = next_block->execute();
  }
  while(next_block != nullptr);

  w.show();
  return a.exec();
}

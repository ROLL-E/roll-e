#include "serverwindow.h"
#include <QApplication>
#include <iostream>
#include "LogicBlock.h"
#include "ModifierBlock.h"
#include "WaitBlock.h"
#include "ValueBlock.h"

using namespace std;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ServerWindow w;

  WaitBlock* block1(new WaitBlock);

 // ModifierBlock* block2(new ModifierBlock);

  LogicBlock* next_block;

  block1->set_wait_turns(2);
  next_block = block1;

  do {
      cout << "väntar" << endl;
      next_block = next_block->execute();
  }
  while(next_block != nullptr);

  ValueBlock* block3(new ValueBlock);

try {
      block3->add_to_attributes("first");
      block3->add_to_attributes("second");
      block3->add_to_attributes("first");
  }
  catch (const exception& e) {
      cout << e.what() << endl;
  }

  list<string> new_list = block3->get_attributes();

  for (list<string>::iterator it = new_list.begin(); it != new_list.end(); ++it)
      cout << *it << endl;

  block3->remove_attribute("second");

  try {
      block3->remove_attribute("second");
  }
  catch (const exception& e) {
      cout << e.what() << endl;
  }

  list<string> new_list2 = block3->get_attributes();

  for (list<string>::iterator it = new_list2.begin(); it != new_list2.end(); ++it)
      cout << *it << endl;

  w.show();
  return a.exec();
}

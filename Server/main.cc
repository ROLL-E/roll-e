#include "serverwindow.h"
#include <QApplication>
#include <iostream>
#include "LogicBlock.h"
#include "ModifierBlock.h"
#include "WaitBlock.h"
#include "ValueBlock.h"
#include "DamageBlock.h"

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

  try {
        block3->add_to_applicable_skills("first");
        block3->add_to_applicable_skills("second");
        block3->add_to_applicable_skills("first");
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
  try {
        block3->add_to_applicable_items(1);
        block3->add_to_applicable_items(2);
        block3->add_to_applicable_items(1);
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

  list<int> new_list = block3->get_applicable_items();

  for (list<int>::iterator it = new_list.begin(); it != new_list.end(); ++it)
      cout << *it << endl;

  block3->remove_applicable_item(2);

  try {
      block3->remove_applicable_item(2);
  }
  catch (const exception& e) {
      cout << e.what() << endl;
  }

  list<int> new_list2 = block3->get_applicable_items();

  for (list<int>::iterator it = new_list2.begin(); it != new_list2.end(); ++it)
      cout << *it << endl;

  DamageBlock* block4(new DamageBlock);

  cout << "DamageBlock test" << endl;

  block4->set_valueblock(block3);

  try {
    block4->execute();
  }

  catch (const exception& e) {
      cout << e.what() << endl;
  }

  w.show();
  return a.exec();
}

#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>

class Item;
class Story;

namespace Ui {
class itemDialog;
}

class itemDialog : public QDialog
{
  Q_OBJECT

public:
  explicit itemDialog(QWidget *parent = 0);
  itemDialog(Item* new_item, QWidget* parent = 0);
  ~itemDialog();

private slots:
  void on_buttonBox_accepted();

  void on_pushButton_clicked();

private:
  Ui::itemDialog *ui;
  Story* story;
  Item* item;
};

#endif // ITEMDIALOG_H

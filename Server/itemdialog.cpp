#include "itemdialog.h"
#include "ui_itemdialog.h"
#include "serverwindow.h"

#include "Story.h"
#include "Item.h"

itemDialog::itemDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::itemDialog),
  story(dynamic_cast<ServerWindow*>(parent)->get_story())
{
  ui->setupUi(this);
}

itemDialog::~itemDialog()
{
  delete ui;
}

void itemDialog::on_buttonBox_accepted()
{
    item = new Item(ui->lineEdit->text());

    for(int i{0}; i < ui->tableWidget->rowCount(); ++i) {
      item->set_attribute(ui->tableWidget->item(i, 0)->text(), ui->tableWidget->item(i,1)->text().toInt());
    }
    story->add_item(item);
}

void itemDialog::on_pushButton_clicked()
{
  ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

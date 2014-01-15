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

itemDialog::itemDialog(Item* new_item, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::itemDialog),
    story(dynamic_cast<ServerWindow*>(parent)->get_story()),
    item(new_item)
{
    ui->setupUi(this);
    ui->lineEdit->setText(item->get_name());

    ui->attrTableWidget->setRowCount(item->get_attributes().size());
    for (int i{0}; i< item->get_attributes().size(); ++i) {
      ui->attrTableWidget->setItem(i,0,new QTableWidgetItem(item->get_attributes().keys().at(i)));
      ui->attrTableWidget->setItem(i,1,new QTableWidgetItem(QString::number(item->get_attributes().values().at(i))));
    }

    ui->modTableWidget->setRowCount(item->get_modifiers().size());
    for (int i{0}; i< item->get_modifiers().size(); ++i) {
      ui->modTableWidget->setItem(i,0,new QTableWidgetItem(item->get_modifiers().keys().at(i)));
      ui->modTableWidget->setItem(i,1,new QTableWidgetItem(QString::number(item->get_modifiers().values().at(i))));
    }
}

itemDialog::~itemDialog()
{
  delete ui;
}

void itemDialog::on_buttonBox_accepted()
{
    bool was_empty{false};
    if (item == nullptr){
        item = new Item(ui->lineEdit->text());
        was_empty = true;
    }
    else
        item->set_name(ui->lineEdit->text());



    for(int i{0}; i < ui->attrTableWidget->rowCount(); ++i) {
        if (ui->attrTableWidget->item(i,0)->text() != "")
      item->set_attribute(ui->attrTableWidget->item(i, 0)->text(), ui->attrTableWidget->item(i,1)->text().toInt());
    }
    for(int i{0}; i < ui->modTableWidget->rowCount(); ++i) {
        if (ui->modTableWidget->item(i,0)->text() != "")
      item->set_modifier(ui->modTableWidget->item(i, 0)->text(), ui->modTableWidget->item(i,1)->text().toInt());
    }
    if (was_empty)
        story->add_item(item);
}

void itemDialog::on_pushButton_clicked()
{
  ui->attrTableWidget->setRowCount(ui->attrTableWidget->rowCount()+1);
  ui->attrTableWidget->setItem(ui->attrTableWidget->rowCount(),0, new QTableWidgetItem("")); // needed to access the new empty cell
}

void itemDialog::on_mod_addButton_clicked()
{
    ui->modTableWidget->setRowCount(ui->modTableWidget->rowCount()+1);
    ui->modTableWidget->setItem(ui->modTableWidget->rowCount(),0, new QTableWidgetItem("")); // needed to access the new empty cell
}

#include "clientwindow.h"
#include "ui_clientwindow.h"
#include "ServerConnection.h"
#include "Character.h"
#include <QStringListModel>
#include <QAbstractItemModel>
#include "../Server/skillmodel.h"
#include "Item.h"
#include "Skill.h"

ClientWindow::ClientWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ClientWindow)
{
  ui->setupUi(this);
}

ClientWindow::~ClientWindow()
{
  delete ui;
}


void ClientWindow::set_serverconnection(ServerConnection* new_connection) {
  connection = new_connection;
  connection->set_clientwindow(this);
}

ServerConnection*ClientWindow::get_serverconnection()
{
  return connection;
}


void ClientWindow::refresh_fields() {
  Character* character = connection->get_controlledChar();
  QStringList strList{};

  ui->name_label->setText(character->get_name());
  ui->curr_weightLabel->setText(QString::number(character->inventory.get_weight()));
  ui->max_weightLabel->setText(QString::number(character->inventory.get_max_weight()));

  ui->attr_tableWidget->setRowCount(character->get_attributes().size());
  for (int i{0}; i< character->get_attributes().size(); ++i) {
    ui->attr_tableWidget->setItem(i,0,new QTableWidgetItem(character->get_attributes().keys().at(i)));
    ui->attr_tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(character->get_attributes().values().at(i))));
  }
  ui->attr_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  SkillModel* skills_model = new SkillModel(character->get_skills());
  ui->SkillView->setModel(skills_model);

  strList.clear();
  for (Item* item : character->inventory.get_items()) {
    strList.append(item->get_name());
  }
  ui->InventoryView->setModel(new QStringListModel(strList));
  ui->InventoryView->setEditTriggers(QAbstractItemView::NoEditTriggers);

  ui->modifers_tableWidget->clear();
  ui->modifers_tableWidget->setRowCount(0);

  ui->item_tableWidget->clear();
  ui->item_tableWidget->setRowCount(0);

}

void ClientWindow::on_SkillView_clicked(const QModelIndex &index)
{
  if (index.isValid()) {
  Skill* skill = connection->get_controlledChar()->get_skills().at(index.row());
  if (skill != nullptr) {
    int i{0};
    ui->modifers_tableWidget->setRowCount(skill->get_modifiers().size());
    for (QString key : skill->get_modifiers().keys()) {
      ui->modifers_tableWidget->setItem(i, 0, new QTableWidgetItem(key));
      ui->modifers_tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(skill->get_modifiers().value(key))));
      ++i;
    }
    ui->modifers_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  }
  ui->item_tableWidget->clear();
  ui->item_tableWidget->setRowCount(0);
}
}

void ClientWindow::on_InventoryView_clicked(const QModelIndex &index)
{
  if (index.isValid()) {
    Item* item = connection->get_controlledChar()->inventory.get_items().at(index.row());
    if (item != nullptr) {
      int i{0};
      ui->modifers_tableWidget->setRowCount(item->get_modifiers().size());
      for (QString key : item->get_modifiers().keys()) {
        ui->modifers_tableWidget->setItem(i,0, new QTableWidgetItem(key));
        ui->modifers_tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(item->get_modifiers().value(key))));
        ++i;
      }
      ui->modifers_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

      i = 0;
      ui->item_tableWidget->setRowCount(item->get_attributes().size());
      for (QString key : item->get_attributes().keys()) {
        ui->item_tableWidget->setItem(i,0,new QTableWidgetItem(key));
        ui->item_tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(item->get_attributes().value(key))));
        ++i;
      }
      ui->item_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

  }
}

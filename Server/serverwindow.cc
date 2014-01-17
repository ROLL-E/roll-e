#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "characterdialog.h"
#include "itemdialog.h"
#include <QStringListModel>
#include <QAbstractItemModel>
#include <QDebug>
#include <QFileDialog>

#include "Story.h"
#include "Character.h"
#include "skillmodel.h"
#include "Item.h"
#include "Skill.h"
#include "GameSave.h"
#include "startdialog.h"

ServerWindow::ServerWindow( QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ServerWindow)
{
  ui->setupUi(this);

}



ServerWindow::~ServerWindow()
{
  delete ui;
}

void ServerWindow::set_story(Story* new_story)
{
  story = new_story;
}

void ServerWindow::show()
{
  QMainWindow::show();
  refresh_fields();
}

void ServerWindow::on_add_charButton_clicked()
{
  characterDialog charDialog(this);
  charDialog.exec();
  refresh_fields();
}

void ServerWindow::refresh_fields() {

  QStringList strList;
  for (quint16 id : story->get_items().keys()) {
    strList.append(story->get_item(id)->get_name());
  }
  ui->item_comboBox->setModel(new QStringListModel(strList));

  QItemSelectionModel* selection = ui->char_listView->selectionModel();

  strList.clear();
  for (Character* character : story->get_characters())
    strList.append(character->get_name());

  ui->char_listView->setModel(new QStringListModel(strList));
  ui->char_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);


  if (selection == nullptr) {
    ui->skills_listView->setModel(nullptr);
    ui->item_listView->setModel(nullptr);

    ui->attr_tableWidget->clear();
    ui->attr_tableWidget->setRowCount(0);
    ui->entity_tableWidget->clear();
    ui->entity_tableWidget->setRowCount(0);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
  }
  else if (selection->currentIndex().isValid()) {
    ui->char_listView->selectionModel()->select(selection->currentIndex(),QItemSelectionModel::Select);
    Character* character{story->get_characters().at(selection->currentIndex().row())};

    ui->char_nameLabel->setText(character->get_name());
    ui->max_weightLabel->setText(QString::number(character->inventory.get_max_weight()));
    ui->curr_weightLabel->setText(QString::number(character->inventory.get_weight()));

    ui->attr_tableWidget->setRowCount(character->get_attributes().size());
    for (int i{0}; i< character->get_attributes().size(); ++i) {
      ui->attr_tableWidget->setItem(i,0,new QTableWidgetItem(character->get_attributes().keys().at(i)));
      ui->attr_tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(character->get_attributes().values().at(i))));
    }
    ui->attr_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    SkillModel* skills_model = new SkillModel(character->get_skills());
    ui->skills_listView->setModel(skills_model);

    strList.clear();
    for (quint16 id : character->inventory.get_items()) {
      strList.append(story->get_item(id)->get_name());
    }
    ui->item_listView->setModel(new QStringListModel(strList));
    ui->item_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->entity_tableWidget->clear();
    ui->entity_tableWidget->setRowCount(0);

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
  }
}



void ServerWindow::on_newCharacter()
{
  refresh_fields();
}

void ServerWindow::on_char_listView_clicked(const QModelIndex&)
{

  refresh_fields();

}

void ServerWindow::on_edit_charButton_clicked()
{
  QItemSelectionModel* selection = ui->char_listView->selectionModel();

  if(selection->currentIndex().isValid()){
    characterDialog charDialog(story->get_characters().at(ui->char_listView->selectionModel()->currentIndex().row()),this);
    charDialog.exec();
  }
  else
    qDebug() << "Not valid charindex";
}

void ServerWindow::on_pushButton_clicked()
{
  QModelIndexList rows = ui->char_listView->selectionModel()->selectedRows();
  if (rows.size() != 0) {
    Character* character = story->get_characters().at(rows.at(0).row());
    if (character != nullptr) {
      character->add_item(story->get_items().values().at(ui->item_comboBox->currentIndex())->get_id());
    }
    refresh_fields();
  }
}

void ServerWindow::on_remove_itemButton_clicked()
{
  Character* character = story->get_characters().at(ui->char_listView->selectionModel()->currentIndex().row());
  QItemSelectionModel* selection = ui->item_listView->selectionModel();
  if (selection != nullptr) {
    character->remove_item(character->inventory.get_items().at(selection->currentIndex().row()));
  }
  refresh_fields();
}


void ServerWindow::on_item_listView_clicked(const QModelIndex &index)
{
  qDebug() << index.row();

  QList<quint16> inventory_items = story->get_characters().at(ui->char_listView->selectionModel()
                                                              ->currentIndex().row())->inventory.get_items();
  if (inventory_items.size() != ui->item_listView->model()->rowCount())
    return;
  Item* item  = story->get_item(inventory_items.at(index.row()));

  if (item != nullptr) {
    int i{0};
    ui->entity_tableWidget->setRowCount(item->get_modifiers().size());
    for (QString key : item->get_modifiers().keys()) {
      ui->entity_tableWidget->setItem(i, 0, new QTableWidgetItem(key));
      ui->entity_tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(item->get_modifiers().value(key))));
      ++i;
    }
    ui->entity_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    i = 0;
    ui->tableWidget->setRowCount(item->get_attributes().size());
    for (QString key : item->get_attributes().keys()) {
      ui->tableWidget->setItem(i,0,new QTableWidgetItem(key));
      ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(item->get_attribute(key))));
      ++i;
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  }


}

void ServerWindow::on_skills_listView_clicked(const QModelIndex &index)
{
  Skill* skill = story->get_characters().at(ui->char_listView->selectionModel()->selectedRows().at(0).row())->get_skills().at(index.row());
  if (skill != nullptr) {
    int i{0};
    ui->entity_tableWidget->setRowCount(skill->get_modifiers().size());
    for (QString key : skill->get_modifiers().keys()) {
      ui->entity_tableWidget->setItem(i, 0, new QTableWidgetItem(key));
      ui->entity_tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(skill->get_modifier(key))));
      ++i;
    }
    ui->entity_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  }
  ui->tableWidget->clear();
  ui->tableWidget->setRowCount(0);
}

void ServerWindow::on_pushButton_2_clicked()
{
  itemDialog dialog(this);
  dialog.exec();
  refresh_fields();
}

void ServerWindow::on_item_modButton_clicked()
{
  if (ui->char_listView->currentIndex().isValid() && ui->item_listView->currentIndex().isValid()) {


    itemDialog mod_dialog(story->get_item(
                            story->get_characters().at(
                              ui->char_listView->currentIndex().row())
                            ->inventory.get_items().at(
                              ui->item_listView->currentIndex().row())),
                          this);
    mod_dialog.exec();

    refresh_fields();
  }
}

void ServerWindow::on_actionSave_story_triggered()
{
  GameSave::save(story,QFileDialog::getSaveFileName(this, "Save current story", QString(), QString()));
}

void ServerWindow::on_actionNew_story_triggered()
{
  StartDialog dlg(this, this);
  dlg.exec();
}

void ServerWindow::on_actionQuit_triggered()
{
  if (story != nullptr)
    delete story;
  QApplication::instance()->quit();
}

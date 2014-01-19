#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "characterdialog.h"
#include "itemdialog.h"
#include "startdialog.h"
#include "skilldialog.h"
#include <QStringListModel>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QDebug>
#include <QFileDialog>

#include "Story.h"
#include "Character.h"
#include "skillmodel.h"
#include "Item.h"
#include "Skill.h"
#include "GameSave.h"
#include "ClientConnection.h"
#include "Scenario.h"
#include "Server.h"

//QML
#include "scenariocontroller.h"



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
  update_characters();
  refresh_fields();
}

void ServerWindow::refresh_fields() {

  QStringList strList;
  for (quint16 id : story->get_items().keys()) {
    strList.append(story->get_item(id)->get_name());
  }
  ui->item_comboBox->setModel(new QStringListModel(strList));


  strList.clear();
  for (Skill* skill : story->get_ruleset()->get_skills()) {
    strList.append(skill->get_name());
  }
  ui->skill_comboBox->setModel(new QStringListModel(strList));

  strList.clear();
  for (Scenario* scen : story->get_scenarios()) {
      strList.append(scen->get_name());
  }
  ui->scenario_comboBox->setModel(new QStringListModel(strList));

  QItemSelectionModel* selection = ui->char_listView->selectionModel();

  if (selection == nullptr || !selection->currentIndex().isValid()) {

    ui->kick_button->setEnabled(false);
    ui->scenario_addButton->setEnabled(false);
    ui->skills_listView->setModel(nullptr);
    ui->item_listView->setModel(nullptr);

    ui->attr_tableWidget->clear();
    ui->attr_tableWidget->setRowCount(0);
    ui->entity_tableWidget->clear();
    ui->entity_tableWidget->setRowCount(0);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    update_characters();

  }
  else if (selection->currentIndex().isValid()) {
    Character* character{story->get_characters().at(selection->currentIndex().row())};

    if (character->get_connection() == nullptr)
      ui->kick_button->setEnabled(false);
    else
      ui->kick_button->setEnabled(true);

    ui->scenario_addButton->setEnabled(true);
    ui->char_nameLabel->setText(character->get_name());
    ui->max_weightLabel->setText(QString::number(character->inventory.get_max_weight()));
    ui->curr_weightLabel->setText(QString::number(character->inventory.get_weight()));

    if (character->get_connection().isNull())
      ui->clientIPLabel->setText("Controlled by GM");
    else
      ui->clientIPLabel->setText(character->get_connection().data()->get_address().toString());

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

void ServerWindow::update_characters() {
  QStringList strList;
  for (Character* character : story->get_characters())
    strList.append(character->get_name());

  ui->char_listView->setModel(new QStringListModel(strList));
  ui->char_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}



void ServerWindow::on_newCharacter()
{
  refresh_fields();
}

void ServerWindow::on_char_listView_clicked(const QModelIndex&)
{

  refresh_fields();

}



void ServerWindow::on_pushButton_clicked()
{
  if (ui->item_comboBox->model()->rowCount() != 0) {
    QModelIndexList rows = ui->char_listView->selectionModel()->selectedRows();
    if (rows.size() != 0) {
      Character* character = story->get_characters().at(rows.at(0).row());
      if (character != nullptr && character->inventory.get_items().indexOf(story->get_items().values().at(ui->item_comboBox->currentIndex())->get_id()) == -1) {
        character->add_item(story->get_items().values().at(ui->item_comboBox->currentIndex())->get_id());
      }
      refresh_fields();
    }
  }
}

void ServerWindow::on_remove_itemButton_clicked()
{
  QItemSelectionModel* selection = ui->item_listView->selectionModel();
  if (selection != nullptr && selection->currentIndex().isValid()) {
    Character* character = story->get_characters().at(ui->char_listView->selectionModel()->currentIndex().row());
    character->remove_item(character->inventory.get_items().at(selection->currentIndex().row()));
  }
  refresh_fields();
}


void ServerWindow::on_item_listView_clicked(const QModelIndex &index)
{
  if (index.isValid())
    qDebug() << "Valid index!: " << index.row();
  QItemSelectionModel* char_selection = ui->char_listView->selectionModel();
  QModelIndex char_index = char_selection->currentIndex();
  if (char_index.isValid())
    qDebug() << "Valid char index!: " << char_index.row();
  else
    return;
  QList<quint16> inventory_items = story->get_characters().at(char_selection->currentIndex().row())->inventory.get_items();
  if (inventory_items.size() != ui->item_listView->model()->rowCount())
    return;
  Item* item  = story->get_item(inventory_items.at(index.row()));

  ui->item_comboBox->setCurrentIndex(story->get_items().values().indexOf(item));

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
  if (ui->char_listView->currentIndex().isValid() && ui->item_comboBox->currentIndex() != -1) {

    itemDialog mod_dialog(story->get_items().values().at(ui->item_comboBox->currentIndex()),this);
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
  update_characters();
  refresh_fields();
}

void ServerWindow::on_actionQuit_triggered()
{
  if (story != nullptr)
    delete story;
  QApplication::instance()->quit();
}

void ServerWindow::on_remove_charButton_clicked()
{
  QItemSelectionModel* selection = ui->char_listView->selectionModel();

  if (selection != nullptr && selection->currentIndex().isValid()) {
    story->remove_character(story->get_characters().at(selection->currentIndex().row()));
  }
  update_characters();
  refresh_fields();
}

void ServerWindow::on_edit_charButton_clicked()
{
  QItemSelectionModel* selection = ui->char_listView->selectionModel();

  if(selection != nullptr && selection->currentIndex().isValid()){
    characterDialog charDialog(story->get_characters().at(selection->currentIndex().row()),this);
    charDialog.exec();
  }
}

void ServerWindow::on_remove_char_skillButton_clicked()
{
  QItemSelectionModel* selection = ui->skills_listView->selectionModel();
  if (selection != nullptr && selection->currentIndex().isValid()) {
    Character* character = story->get_characters().at(ui->char_listView->selectionModel()->currentIndex().row());
    character->remove_skill(character->get_skills().at(selection->currentIndex().row()));
  }
  refresh_fields();
}

void ServerWindow::on_add_skillButton_clicked()
{
  SkillDialog dlg(this);
  dlg.exec();
  refresh_fields();
}

void ServerWindow::on_add_char_skillButton_clicked()
{
  if (ui->skill_comboBox->model()->rowCount() != 0) {
    QModelIndexList rows = ui->char_listView->selectionModel()->selectedRows();
    if (rows.size() != 0) {
      Character* character = story->get_characters().at(rows.at(0).row());
      if (character != nullptr && character->get_skills().indexOf(story->get_ruleset()->get_skills().at(ui->skill_comboBox->currentIndex())) == -1) {
        character->add_skill(story->get_ruleset()->get_skills().at(ui->skill_comboBox->currentIndex()));
      }
      refresh_fields();
    }
  }
}

void ServerWindow::on_skill_modButton_clicked()
{
  if (ui->char_listView->currentIndex().isValid() && ui->skill_comboBox->currentIndex() != -1) {

    SkillDialog mod_dialog(story->get_ruleset()->get_skills().at(ui->skill_comboBox->currentIndex()),this);
    mod_dialog.exec();

    refresh_fields();
  }
}

void ServerWindow::on_remove_skillButton_clicked()
{
  if (ui->skill_comboBox->currentIndex() != -1) {

    Skill* current_skill = story->get_ruleset()->get_skills().at(ui->skill_comboBox->currentIndex());

    for (Character* character : story->get_characters()) {
      for (Skill* skill : character->get_skills()) {
        if (skill == current_skill)
          character->remove_skill(skill);
      }
    }

    story->get_ruleset()->remove_skill(current_skill);
    refresh_fields();
  }

}



void ServerWindow::on_server_startButton_clicked()
{
    story->startServer();
    ui->server_stopButton->setEnabled(true);
    ui->server_startButton->setEnabled(false);
    connect(story->myServer, SIGNAL(client_took_control()), this, SLOT(refresh_fields()));
}

void ServerWindow::on_server_stopButton_clicked()
{
    story->stopServer();
    ui->server_stopButton->setEnabled(false);
    ui->server_startButton->setEnabled(true);
}


void ServerWindow::on_kick_button_clicked()
{
    QItemSelectionModel* selection = ui->char_listView->selectionModel();
    if (selection != nullptr && selection->currentIndex().isValid()) {
         story->myServer->closeConnection(story->myServer->clients.at(selection->currentIndex().row()));
    }
    refresh_fields();
}

void ServerWindow::on_scenario_runButton_clicked()
{
    int selected = ui->scenario_comboBox->currentIndex();
    if (selected != -1){
        Scenario* scenario = story->get_scenarios().at(selected);
        if (scenario->get_next_block() == nullptr)
            scenario->set_next_block(scenario->get_head());
        scenario->run();
    }
    refresh_fields();
}

void ServerWindow::on_scenario_addButton_clicked()
{
   QItemSelectionModel* selection = ui->char_listView->selectionModel();
   if (selection != nullptr && selection->currentIndex().isValid()) {
       ScenarioController* controller;
       controller = new ScenarioController(story->get_characters().at(selection->currentIndex().row()), story->get_characters(),story->get_items(),story->get_ruleset()->get_skills(), story->get_ruleset()->get_attributes());

       connect(controller, SIGNAL(nameChanged()),this,  SLOT(refresh_fields()));
       QQmlContext *ctxt = viewer.rootContext();
       ctxt->setContextProperty("controller", controller);
       viewer.setMainQmlFile(QStringLiteral("qml/GUI-Scenario/main.qml"));
       viewer.showExpanded();

       story->add_scenario(controller->get_scenario());
       refresh_fields();
   }


}


void ServerWindow::on_remove_item_from_gameButton_clicked()
{
  if (ui->item_comboBox->currentIndex() != -1) {

    Item* current_item = story->get_items().values().at(ui->item_comboBox->currentIndex());

    for (Character* character : story->get_characters()) {
      for (Item* item : story->get_items().values()) {
        if (item == current_item)
          character->inventory.remove_item(item->get_id());
      }
    }
   story->remove_item(current_item->get_id());
   refresh_fields();
  }
}

#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "characterdialog.h"
#include <QStringListModel>
#include <QAbstractItemModel>
#include <QDebug>

#include "Story.h"
#include "Character.h"
#include "skillmodel.h"

ServerWindow::ServerWindow(Story* the_story, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ServerWindow),
  story(the_story)
{
  ui->setupUi(this);


  update_characters();
}



ServerWindow::~ServerWindow()
{
  delete ui;
}

void ServerWindow::on_add_charButton_clicked()
{
  characterDialog charDialog(this);
  charDialog.exec();
}

void ServerWindow::update_characters() {
  QStringList strList;
  for (Character* character : story->get_characters())
    strList.append(character->get_name());

  QStringListModel* model = new QStringListModel(strList);
  model->setStringList(strList);
  ui->char_listView->setModel(model);

  if (ui->char_listView->selectionModel()->selectedRows().size() != 0){


  Character* character = story->get_characters().at(ui->char_listView->selectionModel()->selectedRows().at(0).row());

  ui->char_nameLabel->setText(character->get_name());
  ui->max_weightLabel->setText(QString::number(character->inventory.get_max_weight()));
  ui->curr_weightLabel->setText(QString::number(character->inventory.get_weight()));

  SkillModel* skills_model = new SkillModel(character->get_skills());
  ui->skills_listView->setModel(skills_model);

  ui->attr_tableWidget->setRowCount(character->get_attributes().size());
  for (int i{0}; i< character->get_attributes().size(); ++i) {
    ui->attr_tableWidget->setItem(i,0,new QTableWidgetItem(character->get_attributes().keys().at(i)));
    ui->attr_tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(character->get_attributes().values().at(i))));
  }
  }
}

void ServerWindow::on_newCharacter()
{
  update_characters();
}

void ServerWindow::on_char_listView_clicked(const QModelIndex &index)
{
  SkillModel* skill_model = new SkillModel(story->get_characters().at(index.row())->get_skills());
  ui->skills_listView->setModel(skill_model);

  Character* character = story->get_characters().at(index.row());

  ui->char_nameLabel->setText(character->get_name());
  ui->max_weightLabel->setText(QString::number(character->inventory.get_max_weight()));
  ui->curr_weightLabel->setText(QString::number(character->inventory.get_weight()));

  SkillModel* skills_model = new SkillModel(character->get_skills());
  ui->skills_listView->setModel(skills_model);

  ui->attr_tableWidget->setRowCount(character->get_attributes().size());
  for (int i{0}; i< character->get_attributes().size(); ++i) {
    ui->attr_tableWidget->setItem(i,0,new QTableWidgetItem(character->get_attributes().keys().at(i)));
    ui->attr_tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(character->get_attributes().values().at(i))));
  }

}

void ServerWindow::on_edit_charButton_clicked()
{
  if(ui->char_listView->currentIndex().isValid()){
    qDebug() << "valid!";
  characterDialog charDialog(story->get_characters().at(ui->char_listView->currentIndex().row()),this);
  charDialog.exec();
  }
  else
    qDebug() << "minus!";
}

void ServerWindow::on_pushButton_clicked()
{

}

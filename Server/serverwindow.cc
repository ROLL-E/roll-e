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
  qDebug() << strList;
  model->setStringList(strList);
  ui->char_listView->setModel(model);
}

void ServerWindow::on_newCharacter()
{
  update_characters();
}

void ServerWindow::on_char_listView_clicked(const QModelIndex &index)
{
  SkillModel* skill_model = new SkillModel(story->get_characters().at(index.row())->get_skills());
  ui->skills_listView->setModel(skill_model);
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

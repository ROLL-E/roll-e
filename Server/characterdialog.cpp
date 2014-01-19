#include "characterdialog.h"
#include "ui_characterdialog.h"
#include "serverwindow.h"
#include <QStringListModel>
#include <QString>
#include <QDebug>
#include <QList>

#include "Character.h"
#include "Story.h"
#include "Skill.h"
#include "skillmodel.h"

characterDialog::characterDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::characterDialog),
  story(dynamic_cast<ServerWindow*>(parent)->get_story())
{
  ui->setupUi(this);
  connect(this, SIGNAL(newCharacter()), dynamic_cast<ServerWindow*>(parent), SLOT(on_newCharacter()));

  QMap<QString, qint16> attributes;
  for (QString attr: story->get_ruleset()->get_attributes())
    attributes.insert(attr, 0);

  character = new Character(attributes, 0, story);


populate_views();


}

characterDialog::characterDialog(Character *new_char, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::characterDialog),
  story(dynamic_cast<ServerWindow*>(parent)->get_story()),
  character(new_char)
{
  ui->setupUi(this);
  connect(this, SIGNAL(newCharacter()), dynamic_cast<ServerWindow*>(parent), SLOT(on_newCharacter()));

  populate_views();
}

characterDialog::~characterDialog()
{
  delete ui;
}

void characterDialog::on_buttonBox_accepted()
{
  character->set_name(ui->nameLineEdit->text());
  character->inventory.set_max_weight(ui->lineEdit->text().toUInt());
  for (int i{0}; i< character->get_attributes().size(); ++i) {
      if (story->get_ruleset()->get_attributes().contains(ui->attr_tableWidget->item(i,0)->text()))
        character->set_attribute(ui->attr_tableWidget->item(i,0)->text(), ui->attr_tableWidget->item(i,1)->text().toInt());
  }
    if (!story->get_characters().contains(character))
      story->add_character(character);


  emit newCharacter();
  this->hide();
}


void characterDialog::populate_views()
{
  ui->nameLineEdit->setText(character->get_name());
  ui->lineEdit->setText(QString::number(character->inventory.get_max_weight()));


  ui->attr_tableWidget->setRowCount(character->get_attributes().size());
  for (int i{0}; i< character->get_attributes().size(); ++i) {
    ui->attr_tableWidget->setItem(i,0,new QTableWidgetItem(character->get_attributes().keys().at(i)));
    ui->attr_tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(character->get_attributes().values().at(i))));
  }
}

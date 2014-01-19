#include "skilldialog.h"
#include "ui_skilldialog.h"
#include "serverwindow.h"

#include "Skill.h"
#include "Story.h"

SkillDialog::SkillDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SkillDialog),
  story(dynamic_cast<ServerWindow*>(parent)->get_story())
{
  ui->setupUi(this);
}

SkillDialog::SkillDialog(Skill* new_skill, QWidget* parent) :
  QDialog(parent),
  ui(new Ui::SkillDialog),
  story(dynamic_cast<ServerWindow*>(parent)->get_story()),
  skill{new_skill}
{
  ui->setupUi(this);
  ui->lineEdit->setText(skill->get_name());

  ui->tableWidget->setRowCount(skill->get_modifiers().size());
  for (int i{0}; i < skill->get_modifiers().size(); ++i) {
    ui->tableWidget->setItem(i,0,new QTableWidgetItem(skill->get_modifiers().keys().at(i)));
    ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(skill->get_modifiers().values().at(i))));
  }
}

SkillDialog::~SkillDialog()
{
  delete ui;
}

void SkillDialog::on_buttonBox_accepted()
{
    bool was_empty{false};
    if (skill == nullptr){
      skill = new Skill(ui->lineEdit->text());
      was_empty = true;
    }
    else
      skill->set_name(ui->lineEdit->text());

    skill->clear_modifiers();

    for (int i{0}; i < ui->tableWidget->rowCount(); ++i) {
      if (!(!ui->tableWidget->item(i,0)
            || ui->tableWidget->item(i,0)->text().isEmpty()
            || !ui->tableWidget->item(i,1)
            || ui->tableWidget->item(i,1)->text().isEmpty()))
        skill->set_modifier(ui->tableWidget->item(i,0)->text(), ui->tableWidget->item(i,1)->text().toInt());
    }

    if (was_empty)
      story->get_ruleset()->add_skill(skill);


}

void SkillDialog::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount(),0,new QTableWidgetItem("")); //needed to access the new empty cell
}

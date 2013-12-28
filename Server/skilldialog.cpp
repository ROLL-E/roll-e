#include "skilldialog.h"
#include "ui_skilldialog.h"
#include "serverwindow.h"

#include "Story.h"
#include "Skill.h"

skillDialog::skillDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::skillDialog),
  story(dynamic_cast<ServerWindow*>(parent)->get_story())
{
  ui->setupUi(this);
}

skillDialog::~skillDialog()
{
  delete ui;
}

void skillDialog::on_pushButton_clicked()
{
  ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

void skillDialog::on_buttonBox_accepted()
{
  skill = new Skill(ui->lineEdit->text());

  for (int i{0}; i < ui->tableWidget->rowCount(); ++i) {
    skill->set_modifier(ui->tableWidget->item(i,0)->text(), ui->tableWidget->item(i,1)->text().toInt());
  }
  story->get_ruleset()->add_skill(skill);
}

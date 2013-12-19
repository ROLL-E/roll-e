#include "startdialog.h"
#include "ui_startdialog.h"
#include "serverwindow.h"
#include "GameSave.h"
#include "QFileDialog"

#include "Story.h"

startDialog::startDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::startDialog),
  story(nullptr)
{
  ui->setupUi(this);
}

startDialog::~startDialog()
{
  delete ui;
}

void startDialog::on_buttonBox_accepted()
{
  if (story == nullptr) {
    QList<QString> attributes;
    for (int i{0}; i < ui->tableWidget->rowCount(); ++i) {
      attributes.append(ui->tableWidget->item(i,0)->text());
    }

    story = new Story(new Ruleset(attributes));
  }
    parent->set_story(story);
}

void startDialog::on_pushButton_2_clicked()
{
  ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

void startDialog::on_loadButton_clicked()
{
  GameSave::load(QFileDialog::getOpenFileName(), story);
}

#include "startdialog.h"
#include "ui_startdialog.h"
#include "serverwindow.h"
#include "GameSave.h"
#include <QFileDialog>
#include "Story.h"

StartDialog::StartDialog(ServerWindow* window, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::StartDialog),
  main_window{window}
{
  ui->setupUi(this);
}

StartDialog::~StartDialog()
{
  delete ui;
}

void StartDialog::on_pushButton_clicked(){
  Story* story{nullptr};
  GameSave::load(QFileDialog::getOpenFileName(this, "Open saved story", QString(), "Save files (*.sav)"),story);
  main_window->set_story(story);
  hide();
}

void StartDialog::on_pushButton_3_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

void StartDialog::on_pushButton_2_clicked()
{
  QList<QString> list;

  for (int i{0};i<ui->tableWidget->rowCount(); ++i) {
    if (!(!ui->tableWidget->item(i,0) ||
          ui->tableWidget->item(i,0)->text().isEmpty()))
      list.append(ui->tableWidget->item(i,0)->text());
  }
  main_window->set_story(new Story(new Ruleset(list)));
  hide();
}


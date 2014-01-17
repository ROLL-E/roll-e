#include "startdialog.h"
#include "ui_startdialog.h"
#include "serverwindow.h"
#include "GameSave.h"
#include <QFileDialog>

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

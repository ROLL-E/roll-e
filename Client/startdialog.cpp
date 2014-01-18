#include "startdialog.h"
#include "ui_startdialog.h"
#include "ServerConnection.h"
#include "clientwindow.h"

StartDialog::StartDialog(ClientWindow* window, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::StartDialog),
  main_window(window)
{
  ui->setupUi(this);
}

StartDialog::~StartDialog()
{
  delete ui;
}

void StartDialog::on_Connect_Button_clicked() {
  connection = new ServerConnection;
  connection->join(ui->ServerIP_edit->text(),ui->Char_Name_Edit->text());
  connection->clientSocket->waitForConnected();
  main_window->set_serverconnection(connection);
  hide();
}

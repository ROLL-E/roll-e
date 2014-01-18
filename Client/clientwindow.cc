#include "clientwindow.h"
#include "ui_clientwindow.h"
#include "ServerConnection.h"
#include "Character.h"
#include <QStringListModel>
#include <QAbstractItemModel>

ClientWindow::ClientWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ClientWindow)
{
  ui->setupUi(this);
}

ClientWindow::~ClientWindow()
{
  delete ui;
}


void ClientWindow::set_serverconnection(ServerConnection* new_connection) {
  connection = new_connection;
}

ServerConnection*ClientWindow::get_serverconnection()
{
  return connection;
}


void ClientWindow::refresh_fields() {
  Character* character = connection->get_controlledChar();
  QStringList strList{};

  ui->name_label->setText(character->get_name());

  ui->attr_tableWidget->setRowCount(character->get_attributes().size());
  for (int i{0}; i< character->get_attributes().size(); ++i) {
    ui->attr_tableWidget->setItem(i,0,new QTableWidgetItem(character->get_attributes().keys().at(i)));
    ui->attr_tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(character->get_attributes().values().at(i))));
  }
  ui->attr_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

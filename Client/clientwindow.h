#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>

class ServerConnection;

namespace Ui {
  class ClientWindow;
}


class ClientWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit ClientWindow(QWidget *parent = 0);
  ~ClientWindow();

  void refresh_fields();
  void set_serverconnection(ServerConnection*);
  ServerConnection* get_serverconnection();

private slots:
  void on_SkillView_clicked(const QModelIndex &index);

  void on_InventoryView_clicked(const QModelIndex &index);

private:
  Ui::ClientWindow *ui;
  ServerConnection* connection;
};

#endif // CLIENTWINDOW_H

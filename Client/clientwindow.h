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

private:
  Ui::ClientWindow *ui;
  ServerConnection* connection;
};

#endif // CLIENTWINDOW_H

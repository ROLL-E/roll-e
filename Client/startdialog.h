#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

class ServerConnection;
class ClientWindow;

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
  Q_OBJECT

public:
  explicit StartDialog(ClientWindow*, QWidget *parent = 0);
  ~StartDialog();

private:
  Ui::StartDialog *ui;

  ServerConnection* connection{nullptr};
  ClientWindow* main_window;

private slots:

  void on_Connect_Button_clicked();

};

#endif // STARTDIALOG_H

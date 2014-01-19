#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
  class StartDialog;
}

class ServerWindow;

class StartDialog : public QDialog
{
  Q_OBJECT

public:
  explicit StartDialog(ServerWindow*, QWidget *parent = 0);
  ~StartDialog();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::StartDialog *ui;
  ServerWindow* main_window;
};

#endif // STARTDIALOG_H

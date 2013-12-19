#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

class ServerWindow;
class Story;

namespace Ui {
class startDialog;
}

class startDialog : public QDialog
{
  Q_OBJECT

public:
  explicit startDialog(QWidget *parent = 0);
  ~startDialog();

private slots:
  void on_buttonBox_accepted();

  void on_pushButton_2_clicked();

  void on_loadButton_clicked();

private:
  Ui::startDialog *ui;
  ServerWindow* parent;
  Story* story;
};

#endif // STARTDIALOG_H

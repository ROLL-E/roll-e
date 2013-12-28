#ifndef SKILLDIALOG_H
#define SKILLDIALOG_H

#include <QDialog>


class Skill;
class Story;

namespace Ui {
class skillDialog;
}

class skillDialog : public QDialog
{
  Q_OBJECT

public:
  explicit skillDialog(QWidget *parent = 0);
  skillDialog(Skill* new_skill, QWidget* parent = 0);
  ~skillDialog();

private slots:
  void on_pushButton_clicked();

  void on_buttonBox_accepted();

private:
  Ui::skillDialog *ui;
  Story* story;
  Skill* skill;

};

#endif // SKILLDIALOG_H

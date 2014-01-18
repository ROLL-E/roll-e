#ifndef SKILLDIALOG_H
#define SKILLDIALOG_H

#include <QDialog>

namespace Ui {
  class SkillDialog;
}

class Skill;
class Story;

class SkillDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SkillDialog(QWidget *parent);
  SkillDialog(Skill* new_skill,QWidget *parent);
  ~SkillDialog();

private slots:
  void on_buttonBox_accepted();

  void on_pushButton_clicked();

private:
  Ui::SkillDialog *ui;
  Skill* skill{nullptr};
  Story* story{nullptr};
};

#endif // SKILLDIALOG_H

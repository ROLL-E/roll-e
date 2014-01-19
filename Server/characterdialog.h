#ifndef CHARACTERDIALOG_H
#define CHARACTERDIALOG_H

#include <QDialog>


class Story;
class Character;

namespace Ui {
class characterDialog;
}

class characterDialog : public QDialog
{
  Q_OBJECT

public:
  explicit characterDialog(QWidget *parent = 0);
  characterDialog(Character* new_char, QWidget* parent = 0);
  ~characterDialog();

signals:
  void newCharacter();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::characterDialog *ui;
  Story* story;
  Character* character;

  void populate_views();
};

#endif // CHARACTERDIALOG_H

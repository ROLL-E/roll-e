#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

class Story;

namespace Ui {
  class ServerWindow;
}

class ServerWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit ServerWindow(Story*, QWidget *parent = 0);
  ~ServerWindow();
  Story* get_story() { return story;}

private slots:
  void on_add_charButton_clicked();
  void on_newCharacter();

  void on_char_listView_clicked(const QModelIndex &index);

  void on_edit_charButton_clicked();

  void on_pushButton_clicked();

  void on_remove_itemButton_clicked();

  void on_item_listView_clicked(const QModelIndex &index);

  void on_skills_listView_clicked(const QModelIndex &index);

  void on_pushButton_2_clicked();

  void on_item_modButton_clicked();

private:
  Ui::ServerWindow *ui;
  Story* story;

  void update_characters(int row = -1);

};

#endif // SERVERWINDOW_H

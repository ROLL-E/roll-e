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
  explicit ServerWindow( QWidget *parent = 0);
  ~ServerWindow();
  Story* get_story() { return story;}
  void set_story(Story*);
public slots:
  void show();

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

  void on_actionSave_story_triggered();

  void on_actionNew_story_triggered();

  void on_actionQuit_triggered();

  void on_remove_charButton_clicked();

private:
  Ui::ServerWindow *ui;
  Story* story{nullptr};

  void refresh_fields();
  void update_characters();

};

#endif // SERVERWINDOW_H

#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QtQml>
#include "qtquick2applicationviewer.h"

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
  void refresh_fields();

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

  void on_remove_char_skillButton_clicked();

  void on_add_skillButton_clicked();

  void on_add_char_skillButton_clicked();

  void on_skill_modButton_clicked();

  void on_remove_skillButton_clicked();

  void on_server_startButton_clicked();

  void on_server_stopButton_clicked();

  void on_kick_button_clicked();

  void on_scenario_runButton_clicked();

  void on_scenario_addButton_clicked();

private:
  Ui::ServerWindow *ui;
  Story* story{nullptr};
  QtQuick2ApplicationViewer viewer;

  void update_characters();


};

#endif // SERVERWINDOW_H

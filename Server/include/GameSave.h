#ifndef GAMESAVE_H
#define GAMESAVE_H
#include <QString>
#include <QObject>

class Story;

class GameSave : public QObject {
    Q_OBJECT

public:
  Q_INVOKABLE void load(QString, Story*&); // Loads the loaded file into a Story
  void save(Story*, QString); // Saves the Story to a file.

};



#endif // GAMESAVE_H

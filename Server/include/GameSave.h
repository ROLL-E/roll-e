#ifndef GAMESAVE_H
#define GAMESAVE_H
#include <QString>

class Story;

class GameSave {

public:
  static int load(QString, Story*&); // Loads the loaded file into a Story
  static int save(Story*, QString); // Saves the Story to a file.

};



#endif // GAMESAVE_H

#ifndef GAMESAVE_H
#define GAMESAVE_H5
#include <QString>

class Story;

class GameSave {
private:
  // Will probably require Skills and Scenarios, as well as blocks,
  // to be identified by an id


public:
  static int load(QString, Story*&); // Loads the loaded file into a Story
  static int save(Story*, QString); // Saves the Story to a file.

};



#endif // GAMESAVE_H

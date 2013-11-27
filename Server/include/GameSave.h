#ifndef GAMESAVE_H
#define GAMESAVE_H
#include <QString>

class Story;

class GameSave {
private:
  // Will probably require Skills and Scenarios, as well as blocks,
  // to be identified by an id
public:
  GameSave(Story*); // Create an object for saving
  GameSave(QString); // Create an object for loading from a filename

  void load(Story*); // Loads the loaded file into a Story
  void save(QString); // Saves the Story to a file.

};


#endif // GAMESAVE_H

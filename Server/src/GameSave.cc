#include "GameSave.h"
#include <QFile>
#include <QDataStream>

GameSave::GameSave(QString filename) {
  QFile input_file(filename);
  QDataStream in_stream(&input_file);

}

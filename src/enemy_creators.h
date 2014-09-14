#ifndef ENEMY_CREATORS_H
#define ENEMY_CREATORS_H

#include "gameobject.h"

#include <memory>

class DumbEnemyCreator : public ObjectCreator {
 public:
  std::unique_ptr<GameObject> createObject();
  virtual ~DumbEnemyCreator() {}
};

class StraightLineEnemyCreator : public ObjectCreator {
 public:
  std::unique_ptr<GameObject> createObject();
  virtual ~StraightLineEnemyCreator() {}
};

#endif //ENEMY_CREATORS_H

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <queue>

#include "gameobject.h"
#include "map.h"

class World{
 private:
  std::vector<CollisionEvent> getCollisions(GameObject& object);
  void removeObsoleteObjects();
  void addQueuedObjects();
 public:
  ~World();
  void update(double ms);
  void addObject(GameObject& object);
  void removeObject(GameObject& object);

 public:
  Map* currentMap;
  std::vector<GameObject*> gameObjects;
  std::queue<GameObject*> queuedObjects;
};

#endif

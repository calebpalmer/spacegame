#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "gameobject.h"
#include "map.h"

class World{
 private:
  std::vector<CollisionEvent> getCollisions(GameObject& object);
 public:
  ~World();
  void update(double ms);
  void addObject(GameObject& object);
  void removeObject(GameObject& object);

   public:
    Map* currentMap;
    std::vector<GameObject*> gameObjects;
};

#endif

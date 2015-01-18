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

 private:
  GameObject* m_pPlayerShip;
 public:
  ~World();
  void update(double ms);
  void addObject(GameObject& object);
  void removeObject(GameObject& object);
  int countObjects(GameObject::ObjectType objectType) const;
  GameObject* getPlayerObject() const;

 public:
  Map* currentMap;
  std::vector<GameObject*> gameObjects;
  std::vector<GameObject*> queuedObjects;
};

#endif

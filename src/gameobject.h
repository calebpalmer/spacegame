#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "CapEngine.h"

class GameObject{
 public:
  virtual CapEngine::Rectangle boundingPolygon() = 0;
  virtual void render() = 0;
  virtual void handleCollision(CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject) = 0;
  virtual ~GameObject() {};
};

#endif // GAMEOBJECT_H

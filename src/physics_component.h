#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "CapEngine.h"

class GameObject;

class PhysicsComponent {
 public:
  virtual void update(GameObject* object, double timestep) = 0;
  virtual CapEngine::Rectangle boundingPolygon(GameObject* object) = 0;
  virtual void handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject) = 0;

};

#endif // PHYSICSCOMPONENT_H

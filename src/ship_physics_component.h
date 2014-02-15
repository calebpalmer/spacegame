#ifndef SHIP_PHYSICS_COMPONENT
#define SHIP_PHYSICS_COMPONENT

#include "gameobject.h"

class ShipPhysicsComponent : public PhysicsComponent {
 public:
  virtual void update(GameObject* object, double timestep);
  virtual CapEngine::Rectangle  boundingPolygon(const GameObject* object) const;
  virtual bool handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject);
  
 public:
  const int WIDTH = 32;
  const int HEIGHT = 32;
};

#endif

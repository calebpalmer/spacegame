#ifndef BULLET_PHYSICS_COMPONENT
#define BULLET_PHYSICS_COMPONENT

#include "gameobject.h"

class BulletPhysicsComponent : public PhysicsComponent {
 public:
  BulletPhysicsComponent(int width = 10, int height = 10);
  
  virtual void update(GameObject* object, double timestep);
  virtual CapEngine::Rectangle  boundingPolygon(const GameObject* object) const;
  virtual bool handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject);

 private:
  int width;
  int height;
};

#endif

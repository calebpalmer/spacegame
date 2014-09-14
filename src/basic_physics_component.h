#ifndef BASIC_PHYSICS_COMPONENT
#define BASIC_PHYSICS_COMPONENT

#include "gameobject.h"
#include "CapEngine.h"

class BasicPhysicsComponent : public PhysicsComponent {
 public:
 BasicPhysicsComponent(int width, int height) : mWidth(width), mHeight(height) { }
  
  virtual void update(GameObject* object, double timestep);

  virtual CapEngine::Rectangle  boundingPolygon(const GameObject* object) const;

  virtual bool handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject);

 protected:
  int mWidth;
  int mHeight;
};

#endif

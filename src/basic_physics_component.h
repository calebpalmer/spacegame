#ifndef BASIC_PHYSICS_COMPONENT
#define BASIC_PHYSICS_COMPONENT

#include "gameobject.h"
#include "CapEngine.h"

class BasicPhysicsComponent : public PhysicsComponent {
 public:
 BasicPhysicsComponent(int width, int height) : mWidth(width), mHeight(height) { }

  virtual void update(GameObject* object, double timestep) {}

  virtual CapEngine::Rectangle  boundingPolygon(const GameObject* object) const { 
    CapEngine::Rectangle rect;
    rect.x = object->position.x - (this->mWidth / 2.0);
    rect.y = object->position.y - (this->mHeight / 2.0);
    rect.width = this->mWidth;
    rect.height = this->mHeight;
    return rect;
  }

  virtual bool handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject) {
    return false;
  }

 private:
  int mWidth;
  int mHeight;
};

#endif

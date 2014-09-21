#ifndef ENEMY_PHYSICS_COMPONENT
#define ENEMY_PHYSICS_COMPONENT

#include "gameobject.h"
#include "basic_physics_component.h"
#include "CapEngine.h"

class EnemyPhysicsComponent : public BasicPhysicsComponent {
 public:
 EnemyPhysicsComponent(int width, int height) : BasicPhysicsComponent(width, height) { }
  virtual bool handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject);
  virtual void update(GameObject* object, double timestep);
};

#endif

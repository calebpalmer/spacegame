#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>

#include "CapEngine.h"

class GameObject;

class CollisionEvent{
 public:
  GameObject* object1;
  GameObject* object2;
  CapEngine::CollisionType type;
  CapEngine::CollisionClass class_;
};

class PhysicsComponent {
 public:
  virtual void update(GameObject* object, double timestep) = 0;
  virtual CapEngine::Rectangle boundingPolygon(GameObject* object) = 0;
  virtual void handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject) = 0;

};

class GraphicsComponent {
 public:
  virtual void render(GameObject* object) = 0;

};

class InputComponent {
 public:
  virtual void update(GameObject* object) = 0;

};

class GameObject{
 private:
  GameObject(const GameObject&);
  GameObject& operator=(const GameObject&);

 public:
  GameObject() {};
  ~GameObject() {};
  void render();
  void update(double ms);
  CapEngine::Rectangle boundingPolygon();
  void handleCollision(CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject);

 public:
  std::shared_ptr<InputComponent> inputComponent;
  std::shared_ptr<PhysicsComponent> physicsComponent;
  std::shared_ptr<GraphicsComponent> graphicsComponent;

  CapEngine::Vector position;
  CapEngine::Vector orientation;
  CapEngine::Vector velocity;
};

#endif // GAMEOBJECT_H

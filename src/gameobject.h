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
  virtual CapEngine::Rectangle boundingPolygon(const GameObject* object) const = 0;
  virtual bool handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject) = 0;

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

 public:
  GameObject() {};
  ~GameObject() {};
  GameObject& operator=(const GameObject& src);
  void render();
  std::unique_ptr<GameObject> update(double ms) const;
  CapEngine::Rectangle boundingPolygon() const;
  bool handleCollision(CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject);

 public:
  std::shared_ptr<InputComponent> inputComponent;
  std::shared_ptr<PhysicsComponent> physicsComponent;
  std::shared_ptr<GraphicsComponent> graphicsComponent;

  CapEngine::Vector position;
  CapEngine::Vector orientation;
  CapEngine::Vector velocity;
};

#endif // GAMEOBJECT_H

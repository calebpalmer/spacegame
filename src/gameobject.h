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

class CustomComponent {
 public:
  virtual void update(GameObject* object) = 0;
  virtual CustomComponent* clone() const = 0;

};

class AIComponent {
 public:
  virtual void update(GameObject* object) = 0;
  virtual AIComponent* clone() const = 0;
};

class ObjectCreator{
 public:
  virtual std::unique_ptr<GameObject> createObject() = 0;
  virtual ~ObjectCreator() {}
};

typedef long ObjectID;

class GameObject{

 private:
  GameObject(const GameObject&);
  GameObject& operator=(const GameObject&);

 public:
  enum ObjectType {
    InvalidObject = 0,
    PlayerShip,
    EnemyShip,
    Projectile
  };

  enum ObjectState {
    Inactive,
    Starting,
    Active,
    Dying,
    Dead
  };

  GameObject(bool newID = true);
  ~GameObject();
  void render();
  std::unique_ptr<GameObject> update(double ms) const;
  CapEngine::Rectangle boundingPolygon() const;
  bool handleCollision(CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject);
  std::unique_ptr<GameObject> clone() const;
  static ObjectID generateID();


 public:
  std::shared_ptr<InputComponent> inputComponent;
  std::shared_ptr<PhysicsComponent> physicsComponent;
  std::shared_ptr<GraphicsComponent> graphicsComponent;
  std::shared_ptr<CustomComponent> customComponent;
  std::shared_ptr<AIComponent> mpAIComponent;

  CapEngine::Vector position;
  CapEngine::Vector orientation;
  CapEngine::Vector velocity;

  ObjectType objectType;
  ObjectState m_objectState;
  ObjectID m_objectID;
  ObjectID m_parentObjectID;

  static ObjectID nextID;

};


#endif // GAMEOBJECT_H

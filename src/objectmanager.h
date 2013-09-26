#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "CapEngine.h"
#include "ship.h"
#include "projectile.h"

#include <memory>

class ObjectManager{
  enum ObjectType {
    OBJECT_SHIP,
    OBJECT_ENEMY,
    OBJECT_PROJECTILE
  };

 public:
  static ObjectManager& getInstance();
  void addObject(ObjectType type, std::shared_ptr<GameObject> gameObject);
  void removeObject(ObjectType type, GameObject* gameObject);
  void render();
  void update();

 private:
  ObjectManager();
  static ObjectManager* objectManager;

}

#endif // OBJECTMANAGER_H

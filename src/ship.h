#ifndef SHIP_H
#define SHIP_H

#include "CapEngine.h"
#include "gun.h"
#include "gameobject.h"

#include <memory>

#define WIDTH 32
#define HEIGHT 32

class Ship : public GameObject{
 public:
  Ship(CapEngine::VideoManager* videoManagerIn);
  ~Ship();
  CapEngine::Rectangle boundingPolygon(); //GameObject
  void render(); // GameObject
  void handleCollision(CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject);
  void init();
  void move(CapEngine::Vector& direction, CapEngine::real timeStep);
  

 private:
  unsigned int health;
  unsigned int velocity;
  std::unique_ptr<Gun> mainGun;
  CapEngine::Logger logger;
  CapEngine::VideoManager* videoManager;
  CapEngine::Surface* surface;
  CapEngine::Vector position;
};

#endif // SHIP_H



#ifndef SHIP_H
#define SHIP_H

#include "gun.h"
#include "gameobject.h"

#include <memory>

#define WIDTH 32
#define HEIGHT 32

class Ship : public GameObject{
 public:
  Ship();
  ~Ship();
  CapEngine::Rectangle boundingPolygon(); //GameObject
  void render(); // GameObject
  void init();
  void move(CapEngine::Vector direction);
  

 private:
  unsigned int health;
  unsigned int velocity;
  std::unique_ptr<Gun> mainGun;
  CapEngine::Surface* surface;
  CapEngine::Vector position;
};

#endif // SHIP_H



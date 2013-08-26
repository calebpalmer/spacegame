#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"

class Projectile : public GameObject{
 public:
  virtual void velocity() = 0;

  virtual CapEngine::Rectangle boundingPolygon() = 0;  //GameObject
  virtual void render() = 0;  // GameObject
};

#endif // PROJECTILE_H

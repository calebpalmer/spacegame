#ifndef GUN_H
#define GUN_H

#include "gameobject.h"

class Gun : public GameObject{
 public:
  virtual ~Gun() = 0;
  virtual bool fire() = 0;
  virtual int fireRate() = 0;
  virtual int ammoRemaining() = 0;
  virtual int cooldownTime() = 0;
  
  virtual CapEngine::Rectangle boundingPolygon() = 0;  //GameObject
  virtual void render() = 0;  // GameObject
};

#endif // GUN_H

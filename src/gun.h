#ifndef GUN_H
#define GUN_H

#include "gameobject.h"

class Gun {
 public:
  virtual ~Gun() = 0;
  virtual void fire() = 0;
  virtual int fireRate() = 0;
  virtual int ammoRemaining() = 0;
  virtual int cooldownTime() = 0;
};

#endif // GUN_H

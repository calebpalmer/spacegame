#ifndef BASICGUN_H
#define BASICGUN_H

#include "gun.h"

class BasicGun : public Gun {
 public:
  BasicGun();
  ~BasicGun() = {}
  // Gun virtual functions
  void fire();
  int fireRate() ;
  int ammoRemaining() ;
  int cooldownTime() ;
 private:
  // Some kind of abstract bullet factory is needed
  int ammunition;
  int cooldown;
  
}

#endif //BASICGUN_H

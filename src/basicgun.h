#ifndef BASICGUN_H
#define BASICGUN_H

#include "gun.h"

class BasicGun : public Gun {
 public:
  BasicGun();
  BasicGun(const BasicGun&);
  BasicGun& operator=(const BasicGun& src);
  ~BasicGun() {}
  std::unique_ptr<Gun> clone() const;

  // Gun virtual functions
  void fire();
  int ammoRemaining() ;

 private:
  // Some kind of abstract bullet factory is needed
  int ammunition;
  int cooldown; // time in ms between shots fired
  
};

#endif //BASICGUN_H

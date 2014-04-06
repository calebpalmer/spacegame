#ifndef BASICGUN_H
#define BASICGUN_H

#include "gun.h"

#include <string>

#include "CapEngine.h"

class BasicGun : public Gun {
 public:
  BasicGun();
  BasicGun(const BasicGun&);
  BasicGun& operator=(const BasicGun& src);
  ~BasicGun() {}
  std::unique_ptr<Gun> clone() const;

  // Gun virtual functions
  void fire(int x, int y);
  int ammoRemaining() ;

 private:
  // Some kind of abstract bullet factory is needed
  int ammunition;
  double cooldown; // time in ms between shots fired
  double lastFire;

  static CapEngine::PCM* pShotSound;
  const std::string shotSoundPath = "res/basicshot.wav";

};

#endif //BASICGUN_H

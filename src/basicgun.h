#ifndef BASICGUN_H
#define BASICGUN_H

#include "gun.h"

#include <string>

#include "CapEngine.h"
#include "gameobject.h"
#include "world.h"

class BasicGun : public Gun {
 public:
  BasicGun(World* world);
  BasicGun(const BasicGun&);
  BasicGun& operator=(const BasicGun& src);
  ~BasicGun() {}
  std::unique_ptr<Gun> clone() const;

  // Gun virtual functions
  void fire(int x, int y, ObjectID parentID);
  int ammoRemaining() ;

 private:
  // Some kind of abstract bullet factory is needed
  int ammunition;
  double cooldown; // time in ms between shots fired
  double lastFire;
  World* m_pWorld;

  static CapEngine::PCM* pShotSound;
  const std::string shotSoundPath = "res/basicshot.wav";

};

#endif //BASICGUN_H

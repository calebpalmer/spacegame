#include "basicgun.h"

using namespace std;

BasicGun::BasicGun() {
  ammunition = -1;  // unlimited
  cooldown = 500; // ms
}

BasicGun::BasicGun(const BasicGun& src){
  ammunition = src.ammunition;
  cooldown = this->cooldown;
}

unique_ptr<Gun> BasicGun::clone() const {
  unique_ptr<Gun> newGun(new BasicGun(*this));
  return std::move(newGun);
}

BasicGun& BasicGun::operator=(const BasicGun& src){
  if(this != &src){
    ammunition = src.ammunition;
    cooldown = this->cooldown;
  }
  return *this;
}


void BasicGun::fire() {
  // make sure cooltime period has elapsed
  // unleash bullet in gameworld
}

int BasicGun::ammoRemaining() {
  return ammunition;
}

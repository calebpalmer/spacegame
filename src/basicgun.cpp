#include "basicgun.h"

#include "CapEngine.h"
#include "locator.h"
#include "world.h"
#include "bullet_physics_component.h"
#include "bullet_graphics_component.h"
#include "null_input_component.h"
#include "null_custom_component.h"
#include "null_ai_component.h"
#include "locator.h"
#include "asset_constants.h"

#include <memory>
#include <iostream>

using namespace std;
using namespace CapEngine;

PCM* BasicGun::pShotSound = nullptr;

BasicGun::BasicGun(World* world) :
  m_pWorld(world) {
  ammunition = -1;  // unlimited
  lastFire = -1;
  cooldown = 300; // ms
}

BasicGun::BasicGun(const BasicGun& src){
  ammunition = src.ammunition;
  cooldown = this->cooldown;
}

unique_ptr<Gun> BasicGun::clone() const {
  unique_ptr<BasicGun> newGun(new BasicGun(m_pWorld));
  newGun->ammunition = ammunition;
  newGun->cooldown = cooldown;
  newGun->lastFire = lastFire;
  
  unique_ptr<Gun> retGun(newGun.release());
  return std::move(retGun);
}

BasicGun& BasicGun::operator=(const BasicGun& src){
  if(this != &src){
    ammunition = src.ammunition;
    cooldown = this->cooldown;
  }
  return *this;
}


void BasicGun::fire(int x, int y, ObjectID parentID) {
  // make sure cooltime period has elapsed
  double current = currentTime();
  if((lastFire == -1 || (current - lastFire >= cooldown)) 
     && (ammunition != 0)) {
    // unleash bullet in gameworld
    lastFire = current; 

    unique_ptr<GameObject> bullet(new GameObject);

    bullet->position.x = x;
    bullet->position.y = y;
    bullet->position.z = 0.0;

    bullet->velocity.x = 0.0;
    bullet->velocity.y = -200.0;
    bullet->velocity.z = 0;

    unique_ptr<PhysicsComponent> upc(new BulletPhysicsComponent());
    unique_ptr<GraphicsComponent> ugc(new BulletGraphicsComponent());
    unique_ptr<InputComponent> uic(new NullInputComponent);
    unique_ptr<CustomComponent> ucc(new NullCustomComponent);
    unique_ptr<AIComponent> pAIC(new NullAIComponent);

    bullet->physicsComponent.reset(upc.release());
    bullet->graphicsComponent.reset(ugc.release());
    bullet->inputComponent.reset(uic.release());
    bullet->customComponent.reset(ucc.release());
    bullet->mpAIComponent.reset(pAIC.release());
    bullet->objectType = GameObject::Projectile;
    bullet->m_parentObjectID = parentID;
    bullet->m_objectState = GameObject::Active;

    GameObject *p_bullet = bullet.release();
     m_pWorld->addObject(*p_bullet);
    
    // create sound effect
    Locator::assetManager->playSound(BASICSHOTSOUNDID, false);
    
  }
}

int BasicGun::ammoRemaining() {
  return ammunition;
}

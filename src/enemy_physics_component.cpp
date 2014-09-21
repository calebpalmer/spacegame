#include "enemy_physics_component.h"

#include <sstream>

#include "locator.h"
#include "CapEngine.h"

using namespace CapEngine;

bool EnemyPhysicsComponent::handleCollision(GameObject* object, CapEngine::CollisionType type, CapEngine::CollisionClass class_, GameObject* otherObject){
  if(class_ == CapEngine::COLLISION_WALL){
    return true;
  }
  if(class_ != CapEngine::COLLISION_WALL && otherObject->objectType == GameObject::Projectile && otherObject->m_parentObjectID != object->m_objectID){
    std::ostringstream msg;
    msg << "Enemy ID " << object->m_objectID << " Has been hit";
    Locator::logger->log(msg.str(), CapEngine::Logger::CDEBUG);

    object->m_objectState = GameObject::Dead;
    return true;
  }

  return false;
  
}

void EnemyPhysicsComponent::update(GameObject* object, double timestep){
  BasicPhysicsComponent::update(object, timestep);
  
  Rectangle mbr = this->boundingPolygon(object);
  int x, y;
  Locator::videoManager->getWindowResolution(&x, &y);
  Rectangle mapMbr(0.0, 0.0, x, y);

  if(MBRRelate(mbr, mapMbr) == OUTSIDE){
    object->m_objectState = GameObject::Inactive;
  }
}

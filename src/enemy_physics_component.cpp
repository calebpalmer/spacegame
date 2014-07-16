#include "enemy_physics_component.h"

#include <sstream>

#include "locator.h"
#include "CapEngine.h"

bool EnemyPhysicsComponent::handleCollision(GameObject* object, CapEngine::CollisionType type, CapEngine::CollisionClass class_, GameObject* otherObject){
  if(otherObject->objectType == GameObject::Projectile && otherObject->m_parentObjectID != object->m_objectID){
    std::ostringstream msg;
    msg << "Enemy ID " << object->m_objectID << " Has been hit";
    Locator::logger->log(msg.str(), CapEngine::Logger::CDEBUG);

    object->m_objectState = GameObject::Dead;
    return true;
  }

  return false;
  
}


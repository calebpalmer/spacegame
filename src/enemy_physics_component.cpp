#include "enemy_physics_component.h"

bool EnemyPhysicsComponent::handleCollision(GameObject* object, CapEngine::CollisionType type, CapEngine::CollisionClass class_, GameObject* otherObject){
  if(otherObject->objectType == GameObject::Projectile && otherObject->m_parentObjectID != object->m_objectID){
    object->m_objectState = GameObject::Dead;
    return true;
  }

  return false;
  
}


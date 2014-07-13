#include "ship_physics_component.h"

using namespace CapEngine;

 void ShipPhysicsComponent::update(GameObject* object, double timestep){
   Vector displacement = object->velocity;
   displacement.scale((timestep / 1000.0));
   object->position = object->position + displacement;
}

Rectangle ShipPhysicsComponent::boundingPolygon(const GameObject* object) const {
  Rectangle rect;
  rect.x = object->position.x - (this->WIDTH / 2.0);
  rect.y = object->position.y - (this->HEIGHT / 2.0);
  rect.width = this->WIDTH;
  rect.height = this->HEIGHT;
  return rect;
}

bool ShipPhysicsComponent::handleCollision(GameObject* object, CapEngine::CollisionType type, CapEngine::CollisionClass class_, GameObject* otherObject){
  // let the world handle wall collisions
  if(class_ == COLLISION_WALL){
    return false;
  }
  
  // ships own projectiles
  if( otherObject->m_parentObjectID == object->m_objectID ){
    // do nothing
    return true;
  }

  else {
    // game over?
    
  }
  return false;
}


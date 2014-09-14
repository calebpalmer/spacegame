#include "basic_physics_component.h"

using namespace CapEngine;

void BasicPhysicsComponent::update(GameObject* object, double timestep){
   Vector displacement = object->velocity;
   displacement.scale((timestep / 1000.0));
   object->position = object->position + displacement;
}

CapEngine::Rectangle  BasicPhysicsComponent::boundingPolygon(const GameObject* object) const { 
    Rectangle rect;
    rect.x = object->position.x - (this->mWidth / 2.0);
    rect.y = object->position.y - (this->mHeight / 2.0);
    rect.width = this->mWidth;
    rect.height = this->mHeight;
    return rect;
  }

bool BasicPhysicsComponent::handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject) {
    return false;
  }



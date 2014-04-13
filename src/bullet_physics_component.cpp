#include "bullet_physics_component.h"

#include "CapEngine.h"

using namespace CapEngine;

BulletPhysicsComponent::BulletPhysicsComponent(int width, int height)
  : width(width), height(height) { }

void BulletPhysicsComponent::update(GameObject* object, double timestep){
  Vector displacement = object->velocity;
  displacement.scale((timestep / 1000.0));
  object->position = object->position + displacement;

}

CapEngine::Rectangle  BulletPhysicsComponent::boundingPolygon(const GameObject* object) const {
  Rectangle rect;
  rect.x = object->position.x - (this->width / 2.0);
  rect.y = object->position.y - (this->height / 2.0);
  rect.width = this->width;
  rect.height = this->height;
  return rect;

}

bool BulletPhysicsComponent::handleCollision(GameObject* object, CapEngine::CollisionType, CapEngine::CollisionClass, GameObject* otherObject){
  return false;
}

#include "gameobject.h"

using namespace CapEngine;

void GameObject::render(){
  graphicsComponent->render(this);
}

void GameObject::update(double ms){
  inputComponent->update(this);
  physicsComponent->update(this, ms);
}

Rectangle GameObject::boundingPolygon(){
  return physicsComponent->boundingPolygon(this);
}


void GameObject::handleCollision(CapEngine::CollisionType type, CapEngine::CollisionClass class_, GameObject* otherObject){
  physicsComponent->handleCollision(this, type, class_, otherObject);
}

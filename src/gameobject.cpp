#include "gameobject.h"

using namespace CapEngine;
using namespace std;

void GameObject::render(){
  graphicsComponent->render(this);
}

unique_ptr<GameObject> GameObject::update(double ms) const{
  // clone new game object and pas to updates
  unique_ptr<GameObject> newObj(new GameObject);
  *newObj = *this;

  newObj->inputComponent->update(newObj.get());
  newObj->physicsComponent->update(newObj.get(), ms);
  // do collision detection to determine whether the new game object should be kept

  return move(newObj);
}

Rectangle GameObject::boundingPolygon() const {
  return physicsComponent->boundingPolygon(this);
}


void GameObject::handleCollision(CapEngine::CollisionType type, CapEngine::CollisionClass class_, GameObject* otherObject){
  physicsComponent->handleCollision(this, type, class_, otherObject);
}

GameObject& GameObject::operator=(const GameObject& object){
  // make sure objects aren't the same
  if(this != &object){
    //release any other heap objects if needed
    // copy all members
    position = object.position;
    orientation = object.orientation;
    velocity = object.velocity;
    inputComponent = object.inputComponent;
    physicsComponent = object.physicsComponent;
    graphicsComponent = object.graphicsComponent;
  }
  return *this;
}

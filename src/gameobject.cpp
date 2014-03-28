#include "gameobject.h"

#include <iostream>

using namespace CapEngine;
using namespace std;

GameObject::~GameObject(){

}

void GameObject::render(){
  graphicsComponent->render(this);
}

unique_ptr<GameObject> GameObject::update(double ms) const{
#ifdef DEBUG
  switch(objectType){
  case Projectile:
    cout << "Updating Projectile" << endl;
    break;
  case PlayerShip:
    cout << "Updating Player" << endl;
    break;
  case EnemyShip:
    cout << "Updating Enemy ship " << endl;
    break;
  default:
    cout << "Updating Unknown object " << endl;
    break;    
  }
#endif
  // clone new game object and pas to updates
  //  unique_ptr<GameObject> newObj(new GameObject(*this));
  unique_ptr<GameObject> newObj = this->clone();
  //  *newObj = *this;

  if(newObj->inputComponent){
    newObj->inputComponent->update(newObj.get());
  }
  if(newObj->physicsComponent){
    newObj->physicsComponent->update(newObj.get(), ms);
  }
  if(newObj->customComponent){
    newObj->customComponent->update(newObj.get());
  }

  return move(newObj);
}

Rectangle GameObject::boundingPolygon() const {
  return physicsComponent->boundingPolygon(this);
}


bool GameObject::handleCollision(CapEngine::CollisionType type, CapEngine::CollisionClass class_, GameObject* otherObject){
  return physicsComponent->handleCollision(this, type, class_, otherObject);
}

GameObject::GameObject(const GameObject& object){
  position = object.position;
  orientation = object.orientation;
  velocity = object.velocity;
  if(object.inputComponent){
    inputComponent = object.inputComponent;
  }
  if(object.physicsComponent){
    physicsComponent = object.physicsComponent;
  }
  if(object.graphicsComponent){
    graphicsComponent = object.graphicsComponent;
  }
  if(object.customComponent){
    customComponent.reset(object.customComponent->clone());
  }
  objectType = object.objectType;
}

GameObject& GameObject::operator=(const GameObject& object){
  // make sure objects aren't the same
  if(this != &object){
    //release any other heap objects if needed
    // copy all members
    position = object.position;
    orientation = object.orientation;
    velocity = object.velocity;
    if(object.inputComponent){
      inputComponent = object.inputComponent;
    }
    if(object.physicsComponent){
      physicsComponent = object.physicsComponent;
    }
    if(object.graphicsComponent){
      graphicsComponent = object.graphicsComponent;
    }
    if(object.customComponent){
      customComponent.reset(object.customComponent->clone());
    }
    objectType = object.objectType;
  }
  return *this;
}

unique_ptr<GameObject> GameObject::clone() const{
  unique_ptr<GameObject> newObj(new GameObject);

  newObj->position = position;
  newObj->orientation = orientation;
  newObj->velocity = velocity;
  if(inputComponent){
    newObj->inputComponent = inputComponent;
  }
  if(physicsComponent){
    newObj->physicsComponent = physicsComponent;
  }
  if(graphicsComponent){
    newObj->graphicsComponent = graphicsComponent;
  }
  if(customComponent){
    newObj->customComponent.reset(customComponent->clone());
  }
  newObj->objectType = objectType;

  return std::move(newObj);
}

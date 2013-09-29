#include "ship.h"

#include <string>
#include <cassert>
#include <sstream>

using namespace std;
using namespace CapEngine;

Ship::Ship(VideoManager* videoManagerIn) :  health(100), velocity(250) {
  assert(videoManagerIn != nullptr);
  videoManager = videoManagerIn;
  position.x = 600;
  position.y = 800 - (HEIGHT * 2);
}

Ship::~Ship() {
  videoManager->closeSurface(surface);
}

void Ship::init(){
  string imageFile = "res/ship.png";
  surface = videoManager->loadImage(imageFile);
}

Rectangle Ship::boundingPolygon(){
  Rectangle rect;
  rect.x = position.x - (WIDTH / 2.0);
  rect.y = position.y - (HEIGHT / 2.0);
  rect.width = WIDTH;
  rect.height = HEIGHT;
  return rect;
}

void Ship::render(){
  Rectangle rect = boundingPolygon();
  videoManager->drawSurface(rect.x, rect.y, surface);
}

void Ship::move(Vector& direction, real timeStep){
  direction.scale(static_cast<double>(velocity) * (timeStep / 1000.0));
  //direction.scale(velocity);
  Vector newPosition = position + direction;
  
  position = newPosition;
}

void Ship::handleCollision(CollisionType type, CollisionClass class_, GameObject* otherObject){
  if(class_ == COLLISION_WALL){
    switch(type){
    case COLLISION_LEFT:
      position.x += velocity;
      break;
      case COLLISION_RIGHT:
	position.x -= velocity;
	break;
    default:
      break;
    }
  }
}

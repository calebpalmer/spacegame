#include "ship.h"

#include <string>
#include <cassert>
#include <sstream>

#include "ship_input_component.h"
#include "ship_graphics_component.h"
#include "ship_physics_component.h"
#include "ship_custom_component.h"
#include "locator.h"

using namespace std;
using namespace CapEngine;

/** Ship::Ship(VideoManager* videoManagerIn) :  health(100), velocity(250) {
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

*/


unique_ptr<GameObject> makeShip(){
  unique_ptr<GameObject> ship(new GameObject);

  VideoManager* videoManager = Locator::videoManager;
  
  unique_ptr<InputComponent> uic(new ShipInputComponent());
  unique_ptr<PhysicsComponent> upc(new ShipPhysicsComponent());
  unique_ptr<GraphicsComponent> ugc(new ShipGraphicsComponent(videoManager));
  unique_ptr<CustomComponent> ucc(new ShipCustomComponent());
  ship->inputComponent.reset(uic.release());
  ship->physicsComponent.reset(upc.release());
  ship->graphicsComponent.reset(ugc.release());
  ship->customComponent.reset(ucc.release());

  return move(ship);
}

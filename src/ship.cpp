#include "ship.h"

#include <string>
#include <cassert>
#include <sstream>

#include "ship_input_component.h"
#include "ship_graphics_component.h"
#include "ship_physics_component.h"
#include "ship_custom_component.h"
#include "null_ai_component.h"
#include "locator.h"

using namespace std;
using namespace CapEngine;

unique_ptr<GameObject> makeShip(World* world){
  unique_ptr<GameObject> ship(new GameObject);

  unique_ptr<InputComponent> uic(new ShipInputComponent());
  unique_ptr<PhysicsComponent> upc(new ShipPhysicsComponent());
  unique_ptr<GraphicsComponent> ugc(new ShipGraphicsComponent());
  unique_ptr<CustomComponent> ucc(new ShipCustomComponent(world));
  unique_ptr<AIComponent> pAIC(new NullAIComponent());
  ship->inputComponent.reset(uic.release());
  ship->physicsComponent.reset(upc.release());
  ship->graphicsComponent.reset(ugc.release());
  ship->customComponent.reset(ucc.release());
  ship->mpAIComponent.reset(pAIC.release());

  ship->objectType = GameObject::PlayerShip;

  return move(ship);
}

#include "ship_input_component.h"

#include "locator.h"
#include "CapEngine.h"

using namespace CapEngine;

void ShipInputComponent::update(GameObject* object){

  Keyboard* keyboard = Locator::keyboard;
  Keyboard::KeyInfo leftInfo = keyboard->keyMap[Keyboard::CAP_KEYLEFT];
  Keyboard::KeyInfo rightInfo = keyboard->keyMap[Keyboard::CAP_KEYRIGHT];

  // left and right are pressed, do set velocity = (0,0,0)
  if(leftInfo.state == Keyboard::CAP_PRESSED && rightInfo.state == Keyboard::CAP_PRESSED){
    object->velocity.x = 0.0;
    object->velocity.y = 0.0;
    object->velocity.z = 0.0;
  }
  // left is pressed
  if(leftInfo.state == Keyboard::CAP_PRESSED && rightInfo.state == Keyboard::CAP_UNPRESSED){
    object->velocity.x = VELOCITY * (-1);
    object->velocity.y = 0.0;
    object->velocity.z = 0.0;
  }
  // right is pressed
  if(leftInfo.state == Keyboard::CAP_UNPRESSED && rightInfo.state == Keyboard::CAP_PRESSED){
    object->velocity.x = VELOCITY;
    object->velocity.y = 0.0;
    object->velocity.z = 0.0;
  }
  // neither right or left are pressed
  else if (leftInfo.state == Keyboard::CAP_UNPRESSED && rightInfo.state == Keyboard::CAP_UNPRESSED){
    // set object velocity to
    object->velocity.x = 0.0;
    object->velocity.y = 0.0;
    object->velocity.z = 0.0;
  }
}

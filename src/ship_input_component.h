#ifndef SHIP_INPUT_COMPONENT_H
#define SHIP_INPUT_COMPONENT_H

#include "gameobject.h"

class ShipInputComponent : public InputComponent {
  virtual void update(GameObject* object);

 private:
    const double VELOCITY = 60.0;
};

#endif // SHIP_INPUT_COMPONENT_H

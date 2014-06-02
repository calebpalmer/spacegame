#ifndef SHIP_GRAPHICS_COMPONENT_H
#define SHIP_GRAPHICS_COMPONENT_H

#include "gameobject.h"

class ShipGraphicsComponent : public GraphicsComponent {
 public:
  ShipGraphicsComponent();
  virtual void render(GameObject* object);
};

#endif // SHIP_GRAPHICS_COMPONENT_H

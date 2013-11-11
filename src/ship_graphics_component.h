#ifndef SHIP_GRAPHICS_COMPONENT_H
#define SHIP_GRAPHICS_COMPONENT_H

#include "gameobject.h"

class ShipGraphicsComponent : public GraphicsComponent {
 public:
  ShipGraphicsComponent(CapEngine::VideoManager*);
  virtual void render(GameObject* object);

 private:
  CapEngine::VideoManager* videoManager;
  CapEngine::Surface* surface;
};

#endif // SHIP_GRAPHICS_COMPONENT_H

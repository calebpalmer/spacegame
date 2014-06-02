#ifndef BULLET_GRAPHICS_COMPONENT
#define BULLET_GRAPHICS_COMPONENT

#include "gameobject.h"
#include "CapEngine.h"

class BulletGraphicsComponent : public GraphicsComponent {

 public:
  BulletGraphicsComponent();

  virtual void render(GameObject* object);

};

#endif

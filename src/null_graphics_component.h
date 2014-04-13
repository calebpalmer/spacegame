#ifndef NULL_GRAPHICS_COMPONENT_H
#define NULL_GRAPHICS_COMPONENT_H

#include "gameobject.h"

class NullGraphicsComponent : public GraphicsComponent {
 public:
  virtual void render(GameObject* object) {}
};

#endif // NULL_GRAPHICS_COMPONENT_H

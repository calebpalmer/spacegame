#ifndef BULLET_GRAPHICS_COMPONENT
#define BULLET_GRAPHICS_COMPONENT

#include "gameobject.h"
#include "CapEngine.h"

class BulletGraphicsComponent : public GraphicsComponent {

 public:
  BulletGraphicsComponent(CapEngine::VideoManager*);

  virtual void render(GameObject* object);

 private:
  CapEngine::VideoManager* videoManager;
  static CapEngine::Surface* surface;


};

#endif

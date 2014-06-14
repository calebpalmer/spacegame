#ifndef ENEMY_GRAPHICS_COMPONENT_H
#define ENEMY_GRAPHICS_COMPONENT_H

#include "gameobject.h"

class EnemyGraphicsComponent : public GraphicsComponent {
 private:
  EnemyGraphicsComponent(const EnemyGraphicsComponent&);
  EnemyGraphicsComponent& operator=(const EnemyGraphicsComponent&);

  int mTextureId;

 public:
  EnemyGraphicsComponent(int textureId);
  virtual void render(GameObject* object);
};

#endif // ENEMY_GRAPHICS_COMPONENT_H

#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

class GameObject;

class GraphicsComponent {
 public:
  virtual void render(GameObject* object) = 0;

};

#endif // GRAPHICSCOMPONENT_H

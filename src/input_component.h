#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

class GameObject;
  
class InputComponent {
 public:
  virtual void update(GameObject* object) = 0;

};

#endif // INPUTCOMPONENT_H

#ifndef SHIP_CUSTOM_COMPONENT
#define SHIP_CUSTOM_COMPONENT

#include "gameobject.h"
#include "gun.h"

class ShipCustomComponent :  public CustomComponent {
 private:
  std::unique_ptr<Gun> mainGun;
 public:
  ShipCustomComponent();
  virtual void update(GameObject* object);
  virtual CustomComponent* clone() const;

  void fireMainGun(int x, int y, ObjectID parentID);
  
};

#endif

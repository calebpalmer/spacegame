#ifndef SHIP_CUSTOM_COMPONENT
#define SHIP_CUSTOM_COMPONENT

#include "gameobject.h"
#include "gun.h"
#include "world.h"

class ShipCustomComponent :  public CustomComponent {
 private:
  World* m_pWorld;
  std::unique_ptr<Gun> mainGun;
 public:
  ShipCustomComponent(World* world);
  virtual void update(GameObject* object);
  virtual CustomComponent* clone() const;

  void fireMainGun(int x, int y, ObjectID parentID);
  
};

#endif

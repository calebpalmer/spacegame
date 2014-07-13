#include "ship_custom_component.h"

#include "basicgun.h"

ShipCustomComponent::ShipCustomComponent() : mainGun(new BasicGun() ) {
  
}

void ShipCustomComponent::update(GameObject* object){ 
  
}

CustomComponent* ShipCustomComponent::clone() const {
  ShipCustomComponent* newComponent = new ShipCustomComponent();
  // clone member variables
  //  *(newComponent->mainGun.get()) = *(this->mainGun.get());
  newComponent->mainGun.reset((this->mainGun->clone()).release());

  return newComponent;
}


void ShipCustomComponent::fireMainGun(int x, int y, ObjectID parentID){
  mainGun->fire(x, y, parentID);
}

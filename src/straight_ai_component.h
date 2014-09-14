#ifndef STRAIGHT_AI_COMPONENT_H
#define STRAIGHT_AI_COMPONENT_H

#include "gameobject.h"
#include "CapEngine.h"

#include <memory>

class StraightAIComponent : public AIComponent {
 private:
  StraightAIComponent(const StraightAIComponent&);
  StraightAIComponent& operator=(const StraightAIComponent&);
 public:
  StraightAIComponent() {}
  virtual void update(GameObject* object) {}

  virtual AIComponent* clone() const {
    std::unique_ptr<AIComponent> pTempStraightAIComponent(new StraightAIComponent);
    return pTempStraightAIComponent.release();
 }

 private:
};

#endif // STRAIGHT_AI_COMPONENT_H

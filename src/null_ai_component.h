#ifndef NULL_AI_COMPONENT_H
#define NULL_AI_COMPONENT_H

#include "gameobject.h"

#include <memory>

class NullAIComponent : public AIComponent {
 private:
  NullAIComponent(const NullAIComponent&);
  NullAIComponent& operator=(const NullAIComponent&);
 public:
  NullAIComponent() {}
  virtual void update(GameObject* object) {}

  virtual AIComponent* clone() const {
    std::unique_ptr<AIComponent> pTempNullAIComponent(new NullAIComponent);
    return pTempNullAIComponent.release();
 }
};

#endif // NULL_AI_COMPONENT_H

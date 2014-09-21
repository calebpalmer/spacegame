#include "enemy_creators.h"

#include "null_input_component.h"
#include "enemy_graphics_component.h"
#include "enemy_physics_component.h"
#include "null_custom_component.h"
#include "null_ai_component.h"
#include "asset_constants.h"

using namespace std;

unique_ptr<GameObject> DumbEnemyCreator::createObject(){
  unique_ptr<GameObject> pEnemyObject(new GameObject);
  
  unique_ptr<InputComponent> pInputComponent(new NullInputComponent());
  unique_ptr<GraphicsComponent> pGraphicsComponent(new EnemyGraphicsComponent(ENEMYTEXTUREID));
  unique_ptr<PhysicsComponent> pPhysicsComponent(new EnemyPhysicsComponent(32, 32));
  unique_ptr<CustomComponent> pCustomComponent(new NullCustomComponent);
  unique_ptr<AIComponent> pAIComponent(new NullAIComponent);

  pEnemyObject->inputComponent.reset(pInputComponent.release());
  pEnemyObject->graphicsComponent.reset(pGraphicsComponent.release());
  pEnemyObject->physicsComponent.reset(pPhysicsComponent.release());
  pEnemyObject->customComponent.reset(pCustomComponent.release());
  pEnemyObject->mpAIComponent.reset(pAIComponent.release());

  pEnemyObject->objectType = GameObject::EnemyShip;
  pEnemyObject->m_objectState = GameObject::Active;
  
  return std::move(pEnemyObject);

}


unique_ptr<GameObject> StraightLineEnemyCreator::createObject(){
  unique_ptr<GameObject> pEnemyObject(new GameObject);

  unique_ptr<InputComponent> pInputComponent(new NullInputComponent());
  unique_ptr<GraphicsComponent> pGraphicsComponent(new EnemyGraphicsComponent(ENEMYTEXTUREID));
  unique_ptr<PhysicsComponent> pPhysicsComponent(new EnemyPhysicsComponent(32, 32));
  unique_ptr<CustomComponent> pCustomComponent(new NullCustomComponent);
  unique_ptr<AIComponent> pAIComponent(new NullAIComponent);

  pEnemyObject->inputComponent.reset(pInputComponent.release());
  pEnemyObject->graphicsComponent.reset(pGraphicsComponent.release());
  pEnemyObject->physicsComponent.reset(pPhysicsComponent.release());
  pEnemyObject->customComponent.reset(pCustomComponent.release());
  pEnemyObject->mpAIComponent.reset(pAIComponent.release());

  pEnemyObject->objectType = GameObject::EnemyShip;
  pEnemyObject->m_objectState = GameObject::Active;

  pEnemyObject->velocity.y = 100;
  
  return std::move(pEnemyObject);
}

#include "enemy_factory.h"

#include "null_input_component.h"
#include "enemy_graphics_component.h"
#include "basic_physics_component.h"
#include "null_custom_component.h"
#include "null_ai_component.h"
#include "asset_constants.h"

using namespace std;

EnemyFactory::EnemyFactory(std::string enemyConfigPath){ }

unique_ptr<GameObject> EnemyFactory::makeEnemy(int enemyKey){

  unique_ptr<GameObject> pEnemyObject(new GameObject);
  
  unique_ptr<InputComponent> pInputComponent(new NullInputComponent());
  unique_ptr<GraphicsComponent> pGraphicsComponent(new EnemyGraphicsComponent(ENEMYTEXTUREID));
  unique_ptr<PhysicsComponent> pPhysicsComponent(new BasicPhysicsComponent(32, 32));
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

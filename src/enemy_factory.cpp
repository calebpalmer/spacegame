#include "enemy_factory.h"

#include "enemy_creators.h"
#include "locator.h"
#include "CapEngine.h"
#include "null_input_component.h"
#include "enemy_graphics_component.h"
#include "enemy_physics_component.h"
#include "null_custom_component.h"
#include "null_ai_component.h"
#include "asset_constants.h"
#include "enemy_creators.h"

#include <sstream>

using namespace std;
using namespace CapEngine;

EnemyFactory* EnemyFactory::s_pEnemyFactory = nullptr;

EnemyFactory::EnemyFactory(){ 
  unique_ptr<ObjectCreator> pBasicEnemy(new DumbEnemyCreator);
  this->registerEnemy("Dumb", std::move(pBasicEnemy));

  unique_ptr<StraightLineEnemyCreator> pStraightLineEnemy(new StraightLineEnemyCreator);
  this->registerEnemy("Straight", std::move(pStraightLineEnemy));
}

EnemyFactory::~EnemyFactory(){
  for (auto i : m_enemyMap){
    delete i.second;
  }
}

unique_ptr<GameObject> EnemyFactory::makeEnemy(string enemyKey){
  auto i = m_enemyMap.find(enemyKey);
  if(i == m_enemyMap.end()){
    ostringstream msg;
    msg << "ObjectCreator \"" << enemyKey << "\" is not registered registered";
    throw CapEngineException(msg.str());
  }

  unique_ptr<GameObject> pEnemyObject = i->second->createObject();
  return std::move(pEnemyObject);
}

bool EnemyFactory::registerEnemy(std::string enemyKey, unique_ptr<ObjectCreator> creator){
  auto i = m_enemyMap.find(enemyKey);
  if( i != m_enemyMap.end() ){
    ostringstream msg;
    msg << "ObjectCreator \"" << enemyKey << "\" already registered";
    Locator::logger->log(msg.str(), Logger::CDEBUG);
    return false;
  }

  m_enemyMap[enemyKey] = creator.release();
  return true;
}

EnemyFactory* EnemyFactory::getInstance(){
  if(s_pEnemyFactory == nullptr){
    s_pEnemyFactory = new EnemyFactory();
  }
  return s_pEnemyFactory;
}

#include "playstate.h"

#include <stdexcept>
#include <sstream>
#include <memory>
#include <string>
#include <vector>
#include "CapEngine.h"
#include "locator.h"
#include "logger.h"
#include "locator.h"

using namespace std;
using namespace CapEngine;

PlayState::PlayState(){
  Locator::videoManager->getWindowResolution(&m_screenWidth, &m_screenHeight);
}

bool PlayState::onLoad(){
  try{
    unique_ptr<GameObject> upShip = makeShip(&m_world);
    Rectangle mbr = upShip->boundingPolygon();
    real xPos = (m_screenWidth / 2.0) - (mbr.width / 2.0);
    real yPos = m_screenHeight - (2 * mbr.height);
    Vector position(xPos, yPos, 0.0);
    upShip->position = position;
    upShip->m_objectState = GameObject::Active;
    m_world.addObject(*(upShip.release()));

    // add an enemy
    EnemyFactory enemyFactory("dummy");
    auto enemyObject = enemyFactory.makeEnemy(-1);
    enemyObject->position.x  = (m_screenWidth / 2.0) - (enemyObject->boundingPolygon().x / 2.0);
    enemyObject->position.y = 20;
    enemyObject->m_objectState = GameObject::Active;
    m_world.addObject(*(enemyObject.release()));
    
    unique_ptr<Map> pMap(new Map1());
    //upMap.reset(new Map1());
    pMap->init();
    m_world.currentMap = pMap.release();
    
  }
  catch(const exception& e){
    Locator::logger->log(string(e.what()), Logger::CERROR);
    return false;
  }
  return true;
}

bool PlayState::onDestroy(){
  try{
    NULL;
  }
  catch(const exception& e){
    Locator::logger->log(string(e.what()), Logger::CERROR);
    return false;
  }
  
  return true;
}

void PlayState::update(double ms){
  m_world.update(ms);
}

void PlayState::render(){
  m_world.currentMap->render(m_screenWidth, m_screenHeight);
  vector<GameObject*>::iterator iter;
  for(iter = m_world.gameObjects.begin(); iter != m_world.gameObjects.end(); iter++){
    (*iter)->render();
  }

}


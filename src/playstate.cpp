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
#include "spacecombat.h"
#include "start_menu_state.h"
#include "pausestate.h"

using namespace std;
using namespace CapEngine;

PlayState::PlayState(){
  Locator::videoManager->getWindowResolution(&m_screenWidth, &m_screenHeight);
  m_startPause = false;
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
  // chech for pause or reset
  if(Locator::keyboard->keyMap[Keyboard::CAP_BACKSPACE].state == Keyboard::CAP_PRESSED){
    SpaceCombatGame::getInstance()->switchState(*(new StartMenuState()));
    return;
  }
  if(Locator::keyboard->keyMap[Keyboard::CAP_ESCAPE].state == Keyboard::CAP_PRESSED){
    m_startPause = true;
  }
  if(m_startPause && Locator::keyboard->keyMap[Keyboard::CAP_ESCAPE].state == Keyboard::CAP_UNPRESSED){
    SpaceCombatGame::getInstance()->pushState(*(new PauseState()));
    m_startPause = false;
  }

  m_world.update(ms);
}

void PlayState::render(){
  m_world.currentMap->render(m_screenWidth, m_screenHeight);
  vector<GameObject*>::iterator iter;
  for(iter = m_world.gameObjects.begin(); iter != m_world.gameObjects.end(); iter++){
    (*iter)->render();
  }

}


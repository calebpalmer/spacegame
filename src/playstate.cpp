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

PlayState::PlayState(int level) 
  : m_startPause(false), m_level(level) {
  Locator::videoManager->getWindowResolution(&m_screenWidth, &m_screenHeight);
}

bool PlayState::onLoad(){
  try{
    m_levels = parseLevelFile("res/levels.xml");
    m_currentLevel = nullptr;
    for(auto i = m_levels.begin(); i != m_levels.end();  i++){
      if((*i)->getLevelNumber() == m_level){
	m_currentLevel = (*i).get();
      }
    }
    m_currentLevel->start();

    unique_ptr<GameObject> upShip = makeShip(&m_world);
    Rectangle mbr = upShip->boundingPolygon();
    real xPos = (m_screenWidth / 2.0) - (mbr.width / 2.0);
    real yPos = m_screenHeight - (2 * mbr.height);
    Vector position(xPos, yPos, 0.0);
    upShip->position = position;
    upShip->m_objectState = GameObject::Active;
    m_world.addObject(*(upShip.release()));

    unique_ptr<Map> pMap(new Map1());
    //upMap.reset(new Map1());
    pMap->init();
    m_world.currentMap = pMap.release();

    unique_ptr<PCM> pMusic(new PCM("res/The_Spread.wav"));
    m_soundId = Locator::soundPlayer->addSound(pMusic.release());
    
  }
  catch(const exception& e){
    Locator::logger->log(string(e.what()), Logger::CERROR);
    return false;
  }
  return true;
}

bool PlayState::onDestroy(){
  try{
    Locator::soundPlayer->deleteSound(m_soundId);
    return true;
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
  m_currentLevel->update(ms, &m_world);
}

void PlayState::render(){
  m_world.currentMap->render(m_screenWidth, m_screenHeight);
  vector<GameObject*>::iterator iter;
  for(iter = m_world.gameObjects.begin(); iter != m_world.gameObjects.end(); iter++){
    (*iter)->render();
  }

}


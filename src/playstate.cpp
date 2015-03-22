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
#include "victory_state.h"

using namespace std;
using namespace CapEngine;

PlayState::PlayState(int level) 
  : m_startPause(false), m_level(level), m_pTargettingAidSurface(nullptr)
  ,m_drawTargettingAid(false)
{
  Locator::videoManager->getWindowResolution(&m_screenWidth, &m_screenHeight);
}

PlayState::~PlayState(){}

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
    pMap->init();
    m_world.currentMap = pMap.release();

    unique_ptr<PCM> pMusic(new PCM("res/The_Spread.wav"));
    m_soundId = Locator::soundPlayer->addSound(pMusic.release());

    // subscribe for keyboard events
    Locator::eventDispatcher->subscribe(this, keyboardEvent);
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
    Locator::eventDispatcher->unsubscribe(this);
    return true;
  }
  catch(const exception& e){
    Locator::logger->log(string(e.what()), Logger::CERROR);
    return false;
  }
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
  // check for toggling of targetting aid
  //if(Locator::keyboard->keyMap[Keyboard::CAP_
  
  if(m_startPause && Locator::keyboard->keyMap[Keyboard::CAP_ESCAPE].state == Keyboard::CAP_UNPRESSED){
    SpaceCombatGame::getInstance()->pushState(*(new PauseState()));
    m_startPause = false;
  }

  m_world.update(ms);
  m_currentLevel->update(ms, &m_world);

  // Check for end of level
  if( m_currentLevel->wavesRemaining() == 0 && m_world.countObjects(GameObject::EnemyShip) == 0 ) {
    // check for next level
    if(m_currentLevel->getLevelNumber() < m_levels.size() ){
      // goto next level
      SpaceCombatGame::getInstance()->switchState(*(new PlayState(m_currentLevel->getLevelNumber() + 1)));
      return;
    }
    else{
      // end game
      SpaceCombatGame::getInstance()->switchState(*(new VictoryState()));
      return;
    }
  }
  
}

void PlayState::render(){
  m_world.currentMap->render(m_screenWidth, m_screenHeight);
  vector<GameObject*>::iterator iter;
  for(iter = m_world.gameObjects.begin(); iter != m_world.gameObjects.end(); iter++){
    (*iter)->render();
  }

  if(m_drawTargettingAid){
    drawTargetingAid();
  }
  
}

void PlayState::drawTargetingAid(){
  // draw targetting aid
  int startPosX, startPosY;
  GameObject* pPlayerShip = m_world.getPlayerObject();
  if(pPlayerShip != nullptr){
  
    startPosX = pPlayerShip->position.x;
    startPosY = pPlayerShip->position.y - (pPlayerShip->boundingPolygon().height / 2.0);

    int targettingAidSurfaceWith = 5;
    if(m_pTargettingAidSurface == nullptr){
      m_pTargettingAidSurface = Locator::videoManager->createSurface(targettingAidSurfaceWith, startPosY);
      CapEngine::drawLine(3, 0, 3, startPosY, m_pTargettingAidSurface, CapEngine::StripedEdge);
    }

    Locator::videoManager->drawSurface(startPosX, 0, m_pTargettingAidSurface);
  }
}

void PlayState::receiveEvent(const SDL_Event* event, CapEngine::Time* time){
  if(event->type == SDL_KEYUP){
    const SDL_KeyboardEvent* keyboardEvent = reinterpret_cast<const SDL_KeyboardEvent*>(event);
    // Toggle the targetting aid if "t" is pressed
    if(keyboardEvent->type == SDL_KEYUP && keyboardEvent->keysym.sym == SDLK_t){
      m_drawTargettingAid = !m_drawTargettingAid;
    }
  }
}

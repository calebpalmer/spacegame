#include "start_menu_state.h"

#include "CapEngine.h"
#include "locator.h"
#include "asset_constants.h"
#include "playstate.h"
#include "spacecombat.h"
#include "map1.h"

using namespace std;
using namespace CapEngine;

bool StartMenuState::onLoad(){
  // load assets
  m_enterPressed = false;
  m_menuSelection = 0;

  m_pMap.reset(new Map1());
  m_pMap->init();

  Locator::videoManager->getWindowResolution(&m_windowWidth, &m_windowHeight );

  return true;
}

bool StartMenuState::onDestroy(){

  return true;
}

void StartMenuState::render(){
  m_pMap->render(m_windowWidth, m_windowHeight);

  Locator::assetManager->draw(TITLETEXTUREID, Rectangle(0, 0, 800, 400), Rectangle(200, 100, 800, 400));
  
  // for( auto i : m_menuOptions){
    
  // }
  
}

void StartMenuState::update(double ms){
  m_pMap->update(ms);
  if( Locator::keyboard->keyMap[Keyboard::CAP_ENTER].state == Keyboard::CAP_PRESSED ){
    m_enterPressed = true;
  }

  if( m_enterPressed == true && Locator::keyboard->keyMap[Keyboard::CAP_ENTER].state == Keyboard::CAP_UNPRESSED ){
    // start game
    unique_ptr<GameState> pGameState(new PlayState());
    SpaceCombatGame::getInstance()->switchState(*(pGameState.release()));
 }
}

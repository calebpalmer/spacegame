#include "start_menu_state.h"

#include "CapEngine.h"
#include "locator.h"
#include "asset_constants.h"
#include "playstate.h"
#include "spacecombat.h"
#include "map1.h"
#include "textbutton.h"
#include "level.h"

using namespace std;
using namespace CapEngine;

StartMenuState::StartMenuState() :
  m_startNewGame(false){
  // Create UIObjects 
  unique_ptr<TextButton> pStartButton(new TextButton("Play", "res/tahoma.ttf", 40, Vector(-1.0, -1.0)));
  unique_ptr<TextButton> pExitButton(new TextButton("Exit", "res/tahoma.ttf", 40, Vector(-1.0, -1.0)));
  int width = pStartButton->getWidth();
  int height = pStartButton->getHeight();
  int xRes, yRes;
  Locator::videoManager->getWindowResolution(&xRes, &yRes);
  int xStart = (xRes / 2) - (width / 2);
  int yStart = 500;
  int ySpacing = height + 15;
  pStartButton->setPosition(Vector(xStart, yStart));
  pStartButton->registerCallback(this->startButtonCallback, this);
  pExitButton->setPosition(Vector(xStart, 1 * (yStart + ySpacing)));
  pExitButton->registerCallback(this->exitButtonCallback, this);

  // add ui objects
  m_uiObjects.push_back(pStartButton.release());
  m_uiObjects.push_back(pExitButton.release());
}

StartMenuState::~StartMenuState(){
  for (auto& i : m_uiObjects){
    delete i;
  }
}

bool StartMenuState::onLoad(){
  // load assets
  m_enterPressed = false;
  m_menuSelection = 0;

  m_pMap.reset(new Map1());
  m_pMap->init();

  Locator::videoManager->getWindowResolution(&m_windowWidth, &m_windowHeight );
  
  unique_ptr<PCM> pMusic(new PCM("res/The_Spread.wav"));
  m_soundId = Locator::soundPlayer->addSound(pMusic.release());

  return true;
}

bool StartMenuState::onDestroy(){
  Locator::soundPlayer->deleteSound(m_soundId);
  return true;
}

void StartMenuState::render(){
  m_pMap->render(m_windowWidth, m_windowHeight);

  Locator::assetManager->draw(TITLETEXTUREID, Rectangle(0, 0, 800, 400), Rectangle(200, 100, 800, 400));
  
  for( auto& i : m_uiObjects){
    i->render();
  }
  
}

void StartMenuState::update(double ms){
  m_pMap->update(ms);
  for( auto& i : m_uiObjects){
    i->update();
  }
  
  if( Locator::keyboard->keyMap[Keyboard::CAP_ENTER].state == Keyboard::CAP_PRESSED ){
    m_enterPressed = true;
  }

  if( m_enterPressed == true && Locator::keyboard->keyMap[Keyboard::CAP_ENTER].state == Keyboard::CAP_UNPRESSED ){
    // start game
    unique_ptr<GameState> pGameState(new PlayState(1));
    SpaceCombatGame::getInstance()->switchState(*(pGameState.release()));
  }

  if(m_startNewGame){
    unique_ptr<GameState> pGameState(new PlayState(1));
    SpaceCombatGame::getInstance()->switchState(*(pGameState.release()));
  }

  if(m_exitGame){
    SpaceCombatGame::getInstance()->exitGame();
  }
}

void StartMenuState::startButtonCallback(void* context){
  reinterpret_cast<StartMenuState*>(context)->m_startNewGame = true;
}

void StartMenuState::exitButtonCallback(void* context){
  reinterpret_cast<StartMenuState*>(context)->m_exitGame = true; 
}

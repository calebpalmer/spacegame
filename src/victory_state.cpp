#include "victory_state.h"

#include "spacecombat.h"
#include "locator.h"
#include "start_menu_state.h"
#include "asset_constants.h"

#include <memory>

using namespace CapEngine;
using namespace std;

bool VictoryState::onLoad(){
  Locator::eventDispatcher->subscribe(this, keyboardEvent);
  return true;
}

bool VictoryState::onDestroy(){
  return true;
}

void VictoryState::update(double ms){
  // check to see if key was pressed
  //// if pressed return to main menu
  if(m_keyPressed){
    unique_ptr<StartMenuState> p_startMenuState(new StartMenuState);
    SpaceCombatGame::getInstance()->switchState(*(p_startMenuState.release()));
  }
}

void VictoryState::render(){
  // draw victory text
  int xRes, yRes;
  Locator::videoManager->getWindowResolution(&xRes, &yRes);
  
  int surfaceWidth = Locator::assetManager->getTextureWidth(VICTORYTEXTUREID);
  int surfaceHeight = Locator::assetManager->getTextureHeight(VICTORYTEXTUREID);
  
  int x, y;
  x = (xRes / 2.0) - (surfaceWidth / 2.0);
  y = 200;
  Locator::assetManager->draw(VICTORYTEXTUREID, Vector(x, y));
  // draw press any key to continue
}

void VictoryState::receiveEvent(const SDL_Event* event, CapEngine::Time* time){
  // press enter to continue
  if(event->type == SDL_KEYUP && reinterpret_cast<const SDL_KeyboardEvent*>(event)->keysym.sym == SDLK_RETURN){
    m_keyPressed = true;
  }
  delete event;
}

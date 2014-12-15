#include "victory_state.h"
#include "spacecombat.h"
#include "locator.h"
#include "start_menu_state.h"
#include "asset_constants.h"
#include "textbutton.h"

#include <memory>

using namespace CapEngine;
using namespace std;

VictoryState::~VictoryState(){
  for(auto& i : m_uiObjects){
    delete i;
  }
  Locator::eventDispatcher->unsubscribe(this);
}

bool VictoryState::onLoad(){
  Locator::eventDispatcher->subscribe(this, keyboardEvent);

  // create uiobjects
  unique_ptr<TextButton> pContinueButton(new TextButton("Continue","res/tahoma.ttf", 40, Vector(-1.0, -1.0)));
  int startButtonWidth = pContinueButton->getWidth();
  int xRes, yRes;
  Locator::videoManager->getWindowResolution(&xRes, &yRes);
  int xStart = (xRes / 2) - (startButtonWidth / 2);
  // Victory image is 400 pixels high and starts at y=200.
  int yStart = 650;
  pContinueButton->setPosition(Vector(xStart, yStart));
  pContinueButton->registerCallback(VictoryState::continueButtonCallback, this);

  m_uiObjects.push_back(pContinueButton.release());
  return true;
}

bool VictoryState::onDestroy(){
  return true;
}

void VictoryState::update(double ms){
  // update UI
  for (auto& i : m_uiObjects){
    i->update();
  }  

  
  // check to see if key was pressed
  //// if pressed return to main menu
  if(m_continueChosen){
    m_continueChosen = false;
    unique_ptr<StartMenuState> p_startMenuState(new StartMenuState);
    SpaceCombatGame::getInstance()->switchState(*(p_startMenuState.release()));
    return;
  }
}

void VictoryState::render(){
  // draw victory text
  int xRes, yRes;
  Locator::videoManager->getWindowResolution(&xRes, &yRes);
  
  int surfaceWidth = Locator::assetManager->getTextureWidth(VICTORYTEXTUREID);
  
  int x, y;
  x = (xRes / 2.0) - (surfaceWidth / 2.0);
  y = 200;
  Locator::assetManager->draw(VICTORYTEXTUREID, Vector(x, y));

  // render UI
  for (auto& i : m_uiObjects){
    i->render();
  }  
}

void VictoryState::receiveEvent(const SDL_Event* event, CapEngine::Time* time){
  // press enter to continue
  if(event->type == SDL_KEYUP && reinterpret_cast<const SDL_KeyboardEvent*>(event)->keysym.sym == SDLK_RETURN){
    m_continueChosen = true;
  }
  delete event;
}

void VictoryState::continueButtonCallback( void* context){
  reinterpret_cast<VictoryState*>(context)->m_continueChosen = true;
}

#include "pausestate.h"

#include "CapEngine.h"
#include "locator.h"
#include "spacecombat.h"
#include "start_menu_state.h"
#include "textbutton.h"

#include <memory>

using namespace CapEngine;
using namespace std;

void PauseState::render(){
  if(m_uiObjects.size() > 0){
    for ( auto i : m_uiObjects){
      i->render();
  }
  }

}

void PauseState::update(double ms){
  if(m_uiObjects.size() > 0){
    for (auto i : m_uiObjects){
      i->update();
    }
  }
  if(!m_escapePressed && Locator::keyboard->keyMap[Keyboard::CAP_ESCAPE].state == Keyboard::CAP_PRESSED){
    m_escapePressed = true;
  }
  
  if(m_escapePressed  && Locator::keyboard->keyMap[Keyboard::CAP_ESCAPE].state == Keyboard::CAP_UNPRESSED){
    SpaceCombatGame::getInstance()->popState();
    return;
  }
  
}

bool PauseState::onLoad(){
  // add ui
  unique_ptr<TextButton> pResumeButton(new TextButton("Resume", "res/tahoma.ttf", 40, Vector(0, 0)));
  unique_ptr<TextButton> pMainMenuButton(new TextButton("Main Menu", "res/tahoma.ttf", 40, Vector(0,0)));
  int numItems = 2;
  int xres, yres;
  Locator::videoManager->getWindowResolution(&xres, &yres);
  int maxwidth = pMainMenuButton->getWidth();
  int xStart = (xres / 2.0) - (maxwidth / 2.0);
  int menuItemSpacing = 10;
  int maxheight = pResumeButton->getHeight() + pMainMenuButton->getHeight() + ((numItems - 1) * menuItemSpacing);
  int yStart = (yres / 2.0) - (maxheight / 2.0);

  int itemHeight = pResumeButton->getHeight();
  pResumeButton->setPosition(Vector(xStart, yStart));
  pMainMenuButton->setPosition(Vector(xStart, yStart + ((numItems - 1) * (itemHeight + menuItemSpacing) )));

  pResumeButton->registerCallback(this->resumeCallback);
  pMainMenuButton->registerCallback(this->returnToMenuCallback);
  
  m_uiObjects.push_back(pResumeButton.release());
  m_uiObjects.push_back(pMainMenuButton.release());

  m_escapePressed = false;
  return true;
}

bool PauseState::onDestroy(){
  return true;
}

void PauseState::returnToMenuCallback(){
  unique_ptr<StartMenuState> p_startMenuState(new StartMenuState);
  SpaceCombatGame::getInstance()->switchState(*(p_startMenuState.release()));
}

void PauseState::resumeCallback(){
  SpaceCombatGame::getInstance()->popState();
}

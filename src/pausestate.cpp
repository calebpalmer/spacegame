#include "pausestate.h"

#include "CapEngine.h"
#include "locator.h"
#include "spacecombat.h"

using namespace CapEngine;

void PauseState::render(){

}

void PauseState::update(double ms){
  if(!m_escapePressed && Locator::keyboard->keyMap[Keyboard::CAP_ESCAPE].state == Keyboard::CAP_PRESSED){
    m_escapePressed = true;
  }
  
  if(m_escapePressed  && Locator::keyboard->keyMap[Keyboard::CAP_ESCAPE].state == Keyboard::CAP_UNPRESSED){
    SpaceCombatGame::getInstance()->popState();
    return;
  }
  
}

bool PauseState::onLoad(){
  m_escapePressed = false;
  return true;
}

bool PauseState::onDestroy(){
  return true;
}

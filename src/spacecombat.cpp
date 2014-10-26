#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <sstream>

#ifdef UNIX
#include <unistd.h>  // sleep
#endif

#include "spacecombat.h"
#include "map1.h"
#include "locator.h"
#include "playstate.h"
#include "level.h"
#include "start_menu_state.h"

using namespace CapEngine;
using namespace std;

SpaceCombatGame* SpaceCombatGame::theGame = nullptr;

SpaceCombatGame* SpaceCombatGame::getInstance(){
  if(theGame == nullptr){
    theGame = new SpaceCombatGame();
  }
  return theGame;
}

SpaceCombatGame::SpaceCombatGame() : showFPS(false), mouse(3) {
  screenConfig.width = 1200;
  screenConfig.height = 800;
  screenConfig.pDepth = 32;
  screenConfig.opengl = false;

  
#ifdef DEBUG
  logger.currentLevel = Logger::CDEBUG;
#endif

    
}

SpaceCombatGame::~SpaceCombatGame(){
  
}

void SpaceCombatGame::init() {
  // set current directory
  setCurrentDir("../");
  logger.log("current directory is set to " + getCurrentDir(), Logger::CDEBUG);

  // Video
  p_videoManager.reset(new VideoManager());
  p_videoManager->initSystem(screenConfig);

  // subscribe to events
  p_eventDispatcher.reset(new EventDispatcher(p_videoManager.get()));
  p_eventDispatcher->subscribe(this, systemEvent);
  p_eventDispatcher->subscribe(this, keyboardEvent);
  p_eventDispatcher->subscribe(this, mouseEvent);
  logger.log("Events subscribed", Logger::CDEBUG);

  // Sound
  SoundPlayer& soundPlayer = SoundPlayer::getSoundPlayer();
  soundPlayer.setState(UNPAUSE);

  // AssetManager
  unique_ptr<AssetManager> upAssetManager(new AssetManager(*(p_videoManager.get()), soundPlayer, assetFilePath));

  //initialize keyboard map
  keyboard.keyMap[Keyboard::CAP_KEYUP].state = Keyboard::CAP_UNPRESSED;
  keyboard.keyMap[Keyboard::CAP_KEYDOWN].state = Keyboard::CAP_UNPRESSED;
  keyboard.keyMap[Keyboard::CAP_KEYLEFT].state = Keyboard::CAP_UNPRESSED;
  keyboard.keyMap[Keyboard::CAP_KEYRIGHT].state = Keyboard::CAP_UNPRESSED;
  
  // setup locator
  Locator::videoManager = p_videoManager.get();
  Locator::logger = &logger;
  Locator::keyboard = &keyboard;
  Locator::mouse = &mouse;
  Locator::soundPlayer = &soundPlayer;
  Locator::assetManager = upAssetManager.release();
  Locator::eventDispatcher = p_eventDispatcher.get();

  // add starting GameState
  // unique_ptr<GameState> pGameState(new PlayState(screenConfig.width, screenConfig.height));
  // this->pushState(*(pGameState.release()));


  unique_ptr<GameState> pStartMenuState(new StartMenuState());
  this->pushState(*(pStartMenuState.release()));
  //pGameState->onLoad();
  //m_gameStates.push_back(pGameState.release());
  

}

void SpaceCombatGame::loop() {
  double previous = currentTime();
  double lag = 0.0;
  while(!quit){
    double current = currentTime();
    double elapsed = current - previous;
    previous = current;
    lag += elapsed;
    
    //process input
    p_eventDispatcher->getEvents();
    if(p_eventDispatcher->hasEvents()){
      p_eventDispatcher->flushQueue();
    }
    
    while(lag >= MS_PER_UPDATE){
      update();
      lag -= MS_PER_UPDATE;
    }
    
    render(1.0);
  }
  p_videoManager->shutdown();
}

void SpaceCombatGame::update() {
  (m_gameStates.back())->update(MS_PER_UPDATE);
}

void SpaceCombatGame::render(double frameFactor) {  
  // framefactor is for just i've updated past the current frame, so render should interpolate the game objects based on this factor
  // update has updated the game world time ahead of real time
  m_gameStates.back()->render();
  p_videoManager->drawScreen();
}

void SpaceCombatGame::receiveEvent(const SDL_Event* event, Time* time){
  // exit when 'q' is pressed
  if ((event->type == SDL_KEYUP && ((SDL_KeyboardEvent*)event)->keysym.sym == SDLK_q) || event->type == SDL_QUIT){
	quit = true;
	logger.log("quitting. ", Logger::CDEBUG);
	return;
  }
  // update the keyboard
  else if(event->type == SDL_KEYUP || event->type == SDL_KEYDOWN){
    SDLKey ksym = ((SDL_KeyboardEvent*)event)->keysym.sym;
    switch(ksym){
    case SDLK_UP:
      keyboard.keyMap[Keyboard::CAP_KEYUP].state = (event->type == SDL_KEYUP ? Keyboard::CAP_UNPRESSED : Keyboard::CAP_PRESSED);
      break;
    case SDLK_DOWN:
      keyboard.keyMap[Keyboard::CAP_KEYDOWN].state = (event->type == SDL_KEYUP ? Keyboard::CAP_UNPRESSED : Keyboard::CAP_PRESSED);      
      break;
    case SDLK_LEFT:
      keyboard.keyMap[Keyboard::CAP_KEYLEFT].state = (event->type == SDL_KEYUP ? Keyboard::CAP_UNPRESSED : Keyboard::CAP_PRESSED);
      break;
    case SDLK_RIGHT:
      keyboard.keyMap[Keyboard::CAP_KEYRIGHT].state = (event->type == SDL_KEYUP ? Keyboard::CAP_UNPRESSED : Keyboard::CAP_PRESSED);
      break;
    case SDLK_SPACE:
      keyboard.keyMap[Keyboard::CAP_SPACE].state = (event->type == SDL_KEYUP ? Keyboard::CAP_UNPRESSED : Keyboard::CAP_PRESSED);
      break;
    case SDLK_RETURN:
      keyboard.keyMap[Keyboard::CAP_ENTER].state = (event->type == SDL_KEYUP ? Keyboard::CAP_UNPRESSED : Keyboard::CAP_PRESSED);
      break;
    case SDLK_BACKSPACE:
      keyboard.keyMap[Keyboard::CAP_BACKSPACE].state = (event->type == SDL_KEYUP ? Keyboard::CAP_UNPRESSED : Keyboard::CAP_PRESSED);
      break;
    case SDLK_ESCAPE:
      keyboard.keyMap[Keyboard::CAP_ESCAPE].state = (event->type == SDL_KEYUP ? Keyboard::CAP_UNPRESSED : Keyboard::CAP_PRESSED);
      break;

    default:
      break;
    }
  }
  // update the mouse position 
  else if(event->type == SDL_MOUSEMOTION) {
    int x = ((SDL_MouseMotionEvent*)event)->x;
    int y = ((SDL_MouseMotionEvent*)event)->y;
    Locator::mouse->setx(x);
    Locator::mouse->sety(y);
  }
  // update the mouse buttons
  else if(event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP){
    if(((SDL_MouseButtonEvent*)event)->type == SDL_MOUSEBUTTONDOWN){
      switch(((SDL_MouseButtonEvent*)event)->button){
      case SDL_BUTTON_LEFT:
	Locator::mouse->setButtonState(0, true);
	break;
      case SDL_BUTTON_MIDDLE:
	Locator::mouse->setButtonState(1, true);
	break;
      case SDL_BUTTON_RIGHT:
	Locator::mouse->setButtonState(2, true);
	break;
      }
    }
    if(((SDL_MouseButtonEvent*)event)->type == SDL_MOUSEBUTTONUP){
      switch(((SDL_MouseButtonEvent*)event)->button){
      case SDL_BUTTON_LEFT:
	Locator::mouse->setButtonState(0, false);
	break;
      case SDL_BUTTON_MIDDLE:
	Locator::mouse->setButtonState(1, false);
	break;
      case SDL_BUTTON_RIGHT:
	Locator::mouse->setButtonState(2, false);
	break;
      }
    }
  }
  // check to see if fps should be shown
  if(event->type == SDL_KEYUP){
    SDLKey ksym = ((SDL_KeyboardEvent*)event)->keysym.sym;
    if(ksym == SDLK_TAB){
      if(showFPS == true){
	showFPS = false;
	p_videoManager->displayFPS(false);
      }
      else{
	showFPS = true;
	ostringstream ttfStream;
	ttfStream << getCurrentDir() << "/res/tahoma.ttf";
	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;
	p_videoManager->displayFPS(true, ttfStream.str(), r, g, b);
      }

    }
  }
}

void SpaceCombatGame::popState(){
  if(m_gameStates.size() > 0){
    GameState* pPoppedState = m_gameStates.back();
    m_gameStates.pop_back();
    if(pPoppedState->onDestroy() == false){
      Locator::logger->log("Failed to destroy popped state", Logger::CWARNING);
    }
  }
}

void SpaceCombatGame::pushState(GameState& gameState){
  m_gameStates.push_back(&gameState);
  if(m_gameStates.back()->onLoad() == false){
    Locator::logger->log("Failed to init pushed state", Logger::CWARNING);
  }
}

void SpaceCombatGame::switchState(GameState& gameState){
  for(unsigned int i = 0; i < m_gameStates.size(); i++){
    this->popState();
  }
  this->pushState(gameState);
}

void SpaceCombatGame::exitGame(){
  quit = true;
}

int main(){
  try{
    SpaceCombatGame* game = SpaceCombatGame::getInstance();
	game->init();
	game->loop();
	return EXIT_SUCCESS;
  }
  catch (CapEngineException& e){
	cerr << e.what() << endl;
  }
  catch(exception& e){
	cerr << e.what() << endl;	
  }
}

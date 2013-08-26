#include <cstdlib>
#include <stdexcept>
#include <iostream>

#include "spacecombat.h"

using namespace CapEngine;
using namespace std;

SpaceCombatGame::SpaceCombatGame() {
  screenConfig.width = 1200;
  screenConfig.height = 800;
  screenConfig.pDepth = 32;
  screenConfig.opengl = false;

}

void SpaceCombatGame::init() {
  // get Logger
  Logger& logger = Logger::getInstance();

  // set current directory
  setCurrentDir("../");
  logger.log("current directory is set to " + getCurrentDir(), Logger::CDEBUG);

  // subscribe to events
  EventDispatcher& eventDispatcher = EventDispatcher::getInstance();
  eventDispatcher.subscribe(this, systemEvent);
  eventDispatcher.subscribe(this, keyboardEvent);
  logger.log("Events subscribed", Logger::CDEBUG);
  
  VideoManager& videoManager = VideoManager::getInstance();
  videoManager.initSystem(screenConfig);

  // initialise objects
  ship.init();
}

void SpaceCombatGame::loop() {
  while(!quit){
	EventDispatcher& eventDispatcher = EventDispatcher::getInstance();
	eventDispatcher.getEvents();
	if(eventDispatcher.hasEvents()){
	  eventDispatcher.flushQueue();
	}
	update();
	render();
  }
  VideoManager::getInstance().shutdown();
}

void SpaceCombatGame::update() {}

void SpaceCombatGame::render() {
  ship.render();
  VideoManager::getInstance().drawScreen();
}

void SpaceCombatGame::receiveEvent(const SDL_Event* event, Time* time){
  // exit when 'q' is pressed
  if ((event->type == SDL_KEYUP && ((SDL_KeyboardEvent*)event)->keysym.sym == SDLK_q) || event->type == SDL_QUIT){
	quit = true;
	Logger::getInstance().log("quitting. ", Logger::CDEBUG);
	return;
  }
  
}

int main(){
  try{
	SpaceCombatGame game;
	game.init();
	game.loop();
	return EXIT_SUCCESS;
  }
  catch (CapEngineException& e){
	cerr << e.what() << endl;
  }
  catch(exception& e){
	cerr << e.what() << endl;	
  }
}

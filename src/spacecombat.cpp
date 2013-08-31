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

SpaceCombatGame::~SpaceCombatGame(){
  VideoManager::getInstance().closeSurface(background);
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
  
  // initialise background
  background = VideoManager::getInstance().loadImage("res/level1.png");

  //initialize keyboard map
  keyboard.keyMap[Keyboard::CAP_KEYUP].state = Keyboard::CAP_UNPRESSED;
  keyboard.keyMap[Keyboard::CAP_KEYDOWN].state = Keyboard::CAP_UNPRESSED;
  keyboard.keyMap[Keyboard::CAP_KEYLEFT].state = Keyboard::CAP_UNPRESSED;
  keyboard.keyMap[Keyboard::CAP_KEYRIGHT].state = Keyboard::CAP_UNPRESSED;
}

void SpaceCombatGame::loop() {
  while(!quit){
	EventDispatcher& eventDispatcher = EventDispatcher::getInstance();
	eventDispatcher.getEvents();
	if(eventDispatcher.hasEvents()){
	  eventDispatcher.flushQueue();
	}
	timeStep.updateStep();
	update();
	render();
	timeStep.renderStep();
  }
  VideoManager::getInstance().shutdown();
}

void SpaceCombatGame::update() {
  // update objects based on input state (keyboard)
  if(keyboard.keyMap[Keyboard::CAP_KEYLEFT] .state == Keyboard::CAP_PRESSED){
    Vector direction(-1.0, 0.0, 0.0);
    ship.move(direction, timeStep.lastTimeStep);
  }
  else if(keyboard.keyMap[Keyboard::CAP_KEYRIGHT] .state == Keyboard::CAP_PRESSED){
    Vector direction(1.0, 0.0, 0.0);
    ship.move(direction, timeStep.lastTimeStep);   
  }
  else{
    Vector direction(0.0, 0.0, 0.0);
    ship.move(direction, timeStep.lastTimeStep);
  }

  // check for collisions
  vector<CollisionEvent> collisions = getCollisions();
  while(collisions.size() >  0){
    vector<CollisionEvent>::iterator iter;
    for(iter = collisions.begin(); iter != collisions.end(); iter++){
      iter->object1->handleCollision(iter->type, iter->class_, iter->object2);
    }
    collisions = getCollisions();
    }
}

void SpaceCombatGame::render() {
  VideoManager::getInstance().drawSurface(0, 0, background);
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
    default:
      break;
    }
  }
  
}

vector<CollisionEvent> SpaceCombatGame::getCollisions(){
  vector<CollisionEvent> collisions;
  // check for wall collision
  CollisionType colType = detectMBRCollisionInterior(ship.boundingPolygon(), Rectangle(0, 0, screenConfig.width, screenConfig.height));
  if(colType != COLLISION_NONE){
    CollisionEvent event;
    event.object1 = &ship;
    event.object2 =nullptr;
    event.type = colType;
    event.class_ = COLLISION_WALL;
    collisions.push_back(event);
  }
  return collisions;
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

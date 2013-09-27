#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "spacecombat.h"
#include "map1.h"

using namespace CapEngine;
using namespace std;

SpaceCombatGame::SpaceCombatGame() {
  screenConfig.width = 1200;
  screenConfig.height = 800;
  screenConfig.pDepth = 32;
  screenConfig.opengl = false;

}

SpaceCombatGame::~SpaceCombatGame(){

}

void SpaceCombatGame::init() {
  // set current directory
  setCurrentDir("../");
  logger.log("current directory is set to " + getCurrentDir(), Logger::CDEBUG);

  p_videoManager.reset(new VideoManager());
  p_videoManager->initSystem(screenConfig);

  // subscribe to events
  p_eventDispatcher.reset(new EventDispatcher(p_videoManager.get()));
  p_eventDispatcher->subscribe(this, systemEvent);
  p_eventDispatcher->subscribe(this, keyboardEvent);
  logger.log("Events subscribed", Logger::CDEBUG);
  
  // initialise objects
 p_ship.reset(new Ship(p_videoManager.get()));
  p_ship->init();
  p_map.reset(new Map1(p_videoManager.get()));
  p_map->init();
  
  //initialize keyboard map
  keyboard.keyMap[Keyboard::CAP_KEYUP].state = Keyboard::CAP_UNPRESSED;
  keyboard.keyMap[Keyboard::CAP_KEYDOWN].state = Keyboard::CAP_UNPRESSED;
  keyboard.keyMap[Keyboard::CAP_KEYLEFT].state = Keyboard::CAP_UNPRESSED;
  keyboard.keyMap[Keyboard::CAP_KEYRIGHT].state = Keyboard::CAP_UNPRESSED;
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
    
    render();
  }
  p_videoManager->shutdown();
}

void SpaceCombatGame::update() {
  // update objects based on input state (keyboard)
  if(keyboard.keyMap[Keyboard::CAP_KEYLEFT] .state == Keyboard::CAP_PRESSED){
    Vector direction(-1.0, 0.0, 0.0);
    p_ship->move(direction, MS_PER_UPDATE);
  }
  else if(keyboard.keyMap[Keyboard::CAP_KEYRIGHT] .state == Keyboard::CAP_PRESSED){
    Vector direction(1.0, 0.0, 0.0);
    p_ship->move(direction, MS_PER_UPDATE);   
  }
  else{
    Vector direction(0.0, 0.0, 0.0);
    p_ship->move(direction, MS_PER_UPDATE);
  }


  p_map->update(MS_PER_UPDATE);

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
  p_map->render(screenConfig.width, screenConfig.height);
  p_ship->render();
  p_videoManager->drawScreen();
}

void SpaceCombatGame::receiveEvent(const SDL_Event* event, Time* time){
  // exit when 'q' is pressed
  if ((event->type == SDL_KEYUP && ((SDL_KeyboardEvent*)event)->keysym.sym == SDLK_q) || event->type == SDL_QUIT){
	quit = true;
	logger.log("quitting. ", Logger::CDEBUG);
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
  CollisionType colType = detectMBRCollisionInterior(p_ship->boundingPolygon(), Rectangle(0, 0, screenConfig.width, screenConfig.height));
  if(colType != COLLISION_NONE){
    CollisionEvent event;
    event.object1 = p_ship.get();
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

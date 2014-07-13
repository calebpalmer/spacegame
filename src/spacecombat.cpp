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
#include "enemy_factory.h"

using namespace CapEngine;
using namespace std;

SpaceCombatGame::SpaceCombatGame() : showFPS(false) {
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
  logger.log("Events subscribed", Logger::CDEBUG);

  // Sound
  SoundPlayer& soundPlayer = SoundPlayer::getSoundPlayer();
  soundPlayer.setState(UNPAUSE);

  // AssetManager
  unique_ptr<AssetManager> upAssetManager(new AssetManager(*(p_videoManager.get()), soundPlayer, assetFilePath));
  
  // setup locator
  Locator::videoManager = p_videoManager.get();
  Locator::logger = &logger;
  Locator::keyboard = &keyboard;
  Locator::soundPlayer = &soundPlayer;
  Locator::world = &(this->world);
  Locator::assetManager = upAssetManager.release();

  // initialise game objects
  unique_ptr<GameObject> upShip = makeShip();
  Rectangle br = upShip->boundingPolygon();
  real xPos = screenConfig.width / 2.0;
  real yPos = screenConfig.height - br.height - 2.0;
  Vector position(xPos, yPos, 0.0);
  upShip->position = position;
  upShip->m_objectState = GameObject::Active;
  world.addObject(*(upShip.release()));

  // add an enemy
  EnemyFactory enemyFactory("dummy");
  auto enemyObject = enemyFactory.makeEnemy(-1);
  enemyObject->position.x  = (screenConfig.width / 2.0) - (enemyObject->boundingPolygon().x / 2.0);
  enemyObject->position.y = 20;
  enemyObject->m_objectState = GameObject::Active;
  world.addObject(*(enemyObject.release()));

  upMap.reset(new Map1());
  upMap->init();
  world.currentMap = upMap.get();
  
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
    
    render(1.0);
  }
  p_videoManager->shutdown();
}

void SpaceCombatGame::update() {
  // update objects based on input state (keyboard)
 //upShip->update(MS_PER_UPDATE);
  //upMap->update(MS_PER_UPDATE);
  world.currentMap->update(MS_PER_UPDATE);
  world.update(MS_PER_UPDATE);\

  // check for collisions
  /*vector<CollisionEvent> collisions = getCollisions();
    while(collisions.size() >  0){
    vector<CollisionEvent>::iterator iter;
    for(iter = collisions.begin(); iter != collisions.end(); iter++){
      iter->object1->handleCollision(iter->type, iter->class_, iter->object2);
    }
    collisions = getCollisions();
    }*/
    }

void SpaceCombatGame::render(double frameFactor) {  
  // framefactor is for just i've updated past the current frame, so render should interpolate the game objects based on this factor
  // update has updated the game world time ahead of real time
  upMap->render(screenConfig.width, screenConfig.height);
  vector<GameObject*>::iterator iter;
  for(iter = world.gameObjects.begin(); iter != world.gameObjects.end(); iter++){
    (*iter)->render();
    }
  //upShip->render();
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
    case SDLK_SPACE:
      keyboard.keyMap[Keyboard::CAP_SPACE].state = (event->type == SDL_KEYUP ? Keyboard::CAP_UNPRESSED : Keyboard::CAP_PRESSED);
      break;
    default:
      break;
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
  
}

vector<CollisionEvent> SpaceCombatGame::getCollisions(){
  vector<CollisionEvent> collisions;
  // // check for wall collision
  // CollisionType colType = detectMBRCollisionInterior(upShip->boundingPolygon(), Rectangle(0, 0, screenConfig.width, screenConfig.height));
  // if(colType != COLLISION_NONE){
  //   CollisionEvent event;
  //   event.object1 = upShip.get();
  //   event.object2 =nullptr;
  //   event.type = colType;
  //   event.class_ = COLLISION_WALL;
  //   collisions.push_back(event);
  // }
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

#ifndef SPACECOMBATGAME_H
#define SPACECOMBATGAME_H

#include "CapEngine.h"
#include "ship.h"
#include "map.h"
#include "map1.h"
#include "gameobject.h"
#include "gamestate.h"

#include <memory>
#include <vector>

#define MS_PER_UPDATE 16.67 // 60fps
//#define MS_PER_UPDATE 33.33 // 30fps

class SpaceCombatGame : IEventSubscriber{

 public:
  static SpaceCombatGame* getInstance();
  void init();
  void loop();
  void receiveEvent(const SDL_Event* event, CapEngine::Time* time);  // IEventSubscriber
 
 private:
  struct CapEngine::Screen_t screenConfig;
 
 private:
  SpaceCombatGame();
  ~SpaceCombatGame();
  void update();
  void render(double frameFactor);
  void renderBackground();
  std::vector<CollisionEvent> getCollisions();

 private:
  static SpaceCombatGame* theGame;
  bool quit;
  bool showFPS;
  CapEngine::TimeStep timeStep;
  CapEngine::Keyboard keyboard;
  std::unique_ptr<CapEngine::VideoManager> p_videoManager;
  CapEngine::Logger logger;
  std::unique_ptr<CapEngine::EventDispatcher> p_eventDispatcher;
  std::vector< GameState* > m_gameStates;
  const std::string assetFilePath = "res/assets.xml";
};

#endif // SPACECOMBATGAME

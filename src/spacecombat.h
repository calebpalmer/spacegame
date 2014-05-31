#ifndef SPACECOMBATGAME_H
#define SPACECOMBATGAME_H

#include "CapEngine.h"
#include "ship.h"
#include "map.h"
#include "map1.h"
#include "gameobject.h"
#include "world.h"

#include <memory>

#define MS_PER_UPDATE 16.67 // 60fps
//#define MS_PER_UPDATE 33.33 // 30fps

class SpaceCombatGame : IEventSubscriber{

 public:
  SpaceCombatGame();
  ~SpaceCombatGame();
  void init();
  void loop();
  void receiveEvent(const SDL_Event* event, CapEngine::Time* time);  // IEventSubscriber
 
 private:
  struct CapEngine::Screen_t screenConfig;
 
 private:
  void update();
  void render(double frameFactor);
  void renderBackground();
  std::vector<CollisionEvent> getCollisions();

 private:
  bool quit;
  bool showFPS;
  World world;
  std::unique_ptr<Map1> upMap;
  CapEngine::TimeStep timeStep;
  CapEngine::Keyboard keyboard;
  std::unique_ptr<CapEngine::VideoManager> p_videoManager;
  CapEngine::Logger logger;
  std::unique_ptr<CapEngine::EventDispatcher> p_eventDispatcher;
  const std::string assetFilePath = "res/assets.xml";
};

#endif // SPACECOMBATGAME

#ifndef SPACECOMBATGAME_H
#define SPACECOMBATGAME_H

#include "CapEngine.h"
#include "ship.h"
#include "map.h"
#include "map1.h"
#include "gameobject.h"

#include <memory>

#define MS_PER_UPDATE 33.33 // 30fps

struct CollisionEvent{
  GameObject* object1;
  GameObject* object2;
  CapEngine::CollisionType type;
  CapEngine::CollisionClass class_;
};

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
  void render();
  void renderBackground();
  std::vector<CollisionEvent> getCollisions();

 private:
  bool quit;
  std::unique_ptr<Ship> p_ship;
  std::unique_ptr<Map1> p_map;
  CapEngine::TimeStep timeStep;
  CapEngine::Keyboard keyboard;
  std::unique_ptr<CapEngine::VideoManager> p_videoManager;
  CapEngine::Logger logger;
  std::unique_ptr<CapEngine::EventDispatcher> p_eventDispatcher;
};

#endif // SPACECOMBATGAME

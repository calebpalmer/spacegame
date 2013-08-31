#ifndef SPACECOMBATGAME_H
#define SPACECOMBATGAME_H

#include "CapEngine.h"
#include "ship.h"
#include "gameobject.h"

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
  Ship ship;
  CapEngine::TimeStep timeStep;
  CapEngine::Keyboard keyboard;
  CapEngine::Surface* background;
};

#endif // SPACECOMBATGAME

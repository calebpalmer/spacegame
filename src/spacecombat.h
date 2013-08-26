#ifndef SPACECOMBATGAME_H
#define SPACECOMBATGAME_H

#include "CapEngine.h"
#include "ship.h"

class SpaceCombatGame : IEventSubscriber{

 public:
  SpaceCombatGame();
  void init();
  void loop();
  void receiveEvent(const SDL_Event* event, CapEngine::Time* time);  // IEventSubscriber
 
 private:
  struct CapEngine::Screen_t screenConfig;
 
 private:
  void update();
  void render();
 private:
  bool quit;
  Ship ship;
};

#endif // SPACECOMBATGAME

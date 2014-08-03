#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "CapEngine.h"
#include "gamestate.h"
#include "gameobject.h"
#include "world.h"
#include "ship.h"
#include "map1.h"
#include "enemy_factory.h"

class PlayState : public GameState {
 public:
  PlayState();
  virtual ~PlayState() {};
  virtual void render();
  virtual void update(double ms);
  virtual bool onLoad();
  virtual bool onDestroy();

 private:
  int m_screenWidth;
  int m_screenHeight;
  World m_world;

  bool m_startPause;
};

#endif

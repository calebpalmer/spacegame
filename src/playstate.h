#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "CapEngine.h"
#include "gamestate.h"
#include "gameobject.h"
#include "world.h"
#include "ship.h"
#include "map1.h"
#include "enemy_factory.h"
#include "level.h"

#include <vector>
#include <memory>

class PlayState : public GameState, public IEventSubscriber {
 public:
  PlayState(int level);
  virtual ~PlayState();
  virtual void render();
  virtual void update(double ms);
  virtual bool onLoad();
  virtual bool onDestroy();
  virtual void receiveEvent(const SDL_Event* event, CapEngine::Time* time);

 private:
  void drawTargetingAid();
  
  int m_screenWidth;
  int m_screenHeight;
  World m_world;
  long m_soundId;
  bool m_startPause;
  std::vector<std::unique_ptr<Level>> m_levels;
  int m_level;
  Level* m_currentLevel;
  CapEngine::Surface* m_pTargettingAidSurface;
  bool m_drawTargettingAid;
};

#endif

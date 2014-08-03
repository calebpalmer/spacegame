#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "gamestate.h"

class PauseState : public GameState {
 public:
  virtual ~PauseState() {};
  virtual void render();
  virtual void update(double ms);
  virtual bool onLoad();
  virtual bool onDestroy();
 private:
  bool m_escapePressed;

};


#endif // PAUSE_STATE_H

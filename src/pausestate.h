#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "gamestate.h"
#include "uiobject.h"

#include <vector>

class PauseState : public GameState {
 public:
  ~PauseState();
  virtual void render();
  virtual void update(double ms);
  virtual bool onLoad();
  virtual bool onDestroy();
  
  static void returnToMenuCallback();
  static void resumeCallback();
 protected:
  bool m_escapePressed;
  std::vector<UIObject*> m_uiObjects;
};


#endif // PAUSE_STATE_H

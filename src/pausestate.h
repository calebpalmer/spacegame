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
  
  static void returnToMenuCallback(void* context);
  static void resumeCallback(void* context);
 protected:
  bool m_escapePressed;
  bool m_switchToMenuState;
  bool m_resumePlayState;
  std::vector<UIObject*> m_uiObjects;
};


#endif // PAUSE_STATE_H

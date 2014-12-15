#ifndef VICTORY_STATE_H
#define VICTORY_STATE_H

#include "CapEngine.h"
#include "gamestate.h"
#include "uiobject.h"

class VictoryState : public GameState, public  IEventSubscriber {
 public:
  virtual ~VictoryState();
  /// GameState virtuals
  virtual void render();
  virtual void update(double ms);
  virtual bool onLoad();
  virtual bool onDestroy();
  // IEventSubscriber virtual
  virtual void receiveEvent(const SDL_Event* event, CapEngine::Time* time);

  static void continueButtonCallback(void*);

 private:
  bool m_continueChosen;
  std::vector<UIObject*> m_uiObjects;
};

#endif // VICTORY_STATE_H

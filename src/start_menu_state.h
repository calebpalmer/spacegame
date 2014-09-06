#ifndef START_MENU_STATE_H
#define START_MENU_STATE_H

#include "gamestate.h"
#include "map.h"
#include "uiobject.h"


#include <vector>
#include <string>
#include <memory>

class StartMenuState : public GameState {
 public:
  StartMenuState();
  virtual void render();
  virtual void update(double ms);
  virtual bool onLoad();
  virtual bool onDestroy();
  
 private:
  int m_menuSelection;
  bool m_enterPressed;
  int m_windowWidth;
  int m_windowHeight;

  std::unique_ptr<Map> m_pMap; // just for a scrolling background
  std::vector<UIObject*> m_uiObjects;
};

#endif // START_MENU_STATE

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
 public:
  virtual ~GameState() {};
  virtual void render() = 0;
  virtual void update(double ms) = 0;
  virtual bool onLoad() = 0;
  virtual bool onDestroy() = 0;
};

#endif // GAMESTATE_H

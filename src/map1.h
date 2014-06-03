#ifndef MAP1_H
#define MAP1_H

#include "CapEngine.h"
#include "map.h"

class Map1 : public Map {
 public:
  Map1();
  ~Map1();
  void update(CapEngine::real timestep);
  void render(int screenWidth, int screenHeight);
  void init();
  int getWidth();
  int getHeight();

 private:
  float y;
  float velocity;  // pixels per second

 public:
  int width;
  int height;
  
};

#endif //MAP1_H

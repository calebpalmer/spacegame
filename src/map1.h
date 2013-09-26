#ifndef MAP1_H
#define MAP1_H

#include "CapEngine.h"
#include "map.h"

class Map1 : public Map {
 public:
  Map1(CapEngine::VideoManager* videoManager);
  ~Map1();
  void update(CapEngine::real timestep);
  void render(int screenWidth, int screenHeight);
  void init();

 private:
  CapEngine::VideoManager* videoManager;
  CapEngine::Surface* surface;
  float y;
  float velocity;  // pixels per second
  int width;
  int height;


};

#endif //MAP1_H

#ifndef MAP_H
#define MAP_H

#include "CapEngine.h"

class Map{
 public:
  virtual ~Map() {}
  virtual void update(CapEngine::real timestep) = 0;
  virtual void render(int screenWidth, int screenHeight) = 0;
  virtual void init() = 0;
  virtual int getWidth() = 0;
  virtual int getHeight() = 0;
 public:
  int width;
  int height;
};

#endif //MAP_H

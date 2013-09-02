#ifndef MAP_H
#define MAP_H

class Map{
 public:
  virtual ~Map() {}
  virtual void update(CapEngine::real timestep) = 0;
  virtual void render(int screenWidth, int screenHeight) = 0;
  virtual void init() = 0;
};

#endif //MAP_H

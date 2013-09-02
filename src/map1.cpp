#include "map1.h"

using namespace CapEngine;

void Map1::init(){
  width = 1200;
  height = 2400;
  y = height;
  velocity = 5;
  surface = VideoManager::getInstance().loadImage("res/level1.png");
}

Map1::~Map1() {}

void Map1::update(real timestep){
  y -= velocity * (1.0f / timestep);
  if( y < 0 ){
    y = height + y;
  }
}

void Map1::render(int screenWidth, int screenHeight){
  VideoManager& videoManager = VideoManager::getInstance();
  // whats left of map
  if(y - screenHeight < 0){
    Logger::getInstance().log("Map cutoff reached", Logger::CDEBUG);
    int yStart = screenHeight - y;
    Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = y;
    videoManager.drawSurface(0, yStart, surface, &rect);

    // start of the map again
    rect.y = height - (screenHeight - y);
    rect.h = screenHeight - y;
    videoManager.drawSurface(0, 0, surface, &rect);

  }
  else{
    Rect rect;
    rect.x = 0;
    rect.y = y - screenHeight;
    rect.w = screenWidth;
    rect.h = screenHeight;
    videoManager.drawSurface(0, 0, surface, &rect);
  }
}



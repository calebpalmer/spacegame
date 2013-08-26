#include "ship.h"

#include <string>

using namespace std;
using namespace CapEngine;

Ship::Ship() {
  position.x = 600;
  position.y = 800 - (HEIGHT * 2);
}

Ship::~Ship() {
  VideoManager::getInstance().closeSurface(surface);
}

void Ship::init(){
  string imageFile = "res/ship.png";
  surface = VideoManager::getInstance().loadImage(imageFile);
}

Rectangle Ship::boundingPolygon(){
  Rectangle rect;
  rect.x = position.x - (WIDTH / 2.0);
  rect.y = position.y - (HEIGHT / 2.0);
  rect.width = WIDTH;
  rect.height = HEIGHT;
  return rect;
}

void Ship::render(){
  Rectangle rect = boundingPolygon();
  VideoManager::getInstance().drawSurface(rect.x, rect.y, surface);
}

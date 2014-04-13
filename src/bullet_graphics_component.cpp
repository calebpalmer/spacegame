#include "bullet_graphics_component.h"

#include <cassert>
#include <string>

using namespace CapEngine;
using namespace std;

Surface* BulletGraphicsComponent::surface = nullptr;

BulletGraphicsComponent::BulletGraphicsComponent(CapEngine::VideoManager* videoManagerIn){
  assert(videoManagerIn != nullptr);
  videoManager = videoManagerIn;
  
  string imageFile = "res/bullet.png";
  if(surface == nullptr){
    surface = videoManager->loadImage(imageFile); // this should be cached
  }
}

void BulletGraphicsComponent::render(GameObject* object){
  Rectangle rect = object->boundingPolygon();
  videoManager->drawSurface(rect.x, rect.y, surface);
}

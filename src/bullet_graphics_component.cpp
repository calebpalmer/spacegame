#include "bullet_graphics_component.h"
#include "asset_constants.h"
#include "locator.h"

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
  Rectangle dstRect = object->boundingPolygon();
  Rectangle srcRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.width = dstRect.width;
  srcRect.height = dstRect.height;

  AssetManager* assetManager = Locator::assetManager;
  assetManager->draw(BULLETTEXTUREID, srcRect, dstRect);
  //videoManager->drawSurface(rect.x, rect.y, surface);
}

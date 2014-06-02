#include "bullet_graphics_component.h"
#include "asset_constants.h"
#include "locator.h"

#include <cassert>
#include <string>

using namespace CapEngine;
using namespace std;

BulletGraphicsComponent::BulletGraphicsComponent() {}

void BulletGraphicsComponent::render(GameObject* object){
  Rectangle dstRect = object->boundingPolygon();
  Rectangle srcRect;
  srcRect.x = 0;
  srcRect.y = 0;
  //srcRect.width = dstRect.width;
  //srcRect.height = dstRect.height;

  AssetManager* assetManager = Locator::assetManager;
  assetManager->draw(BULLETTEXTUREID, srcRect, dstRect);

}

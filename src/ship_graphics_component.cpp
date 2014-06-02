#include "ship_graphics_component.h"

#include <assert.h>
#include <string>

#include "asset_constants.h"
#include "locator.h"

using namespace CapEngine;
using namespace std;

ShipGraphicsComponent::ShipGraphicsComponent() {}

void ShipGraphicsComponent::render(GameObject* object){
  Rectangle dstRect = object->boundingPolygon();
  Rectangle srcRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.width = dstRect.width;
  srcRect.height = dstRect.height;

  AssetManager* assetManager = Locator::assetManager;
  assetManager->draw(SHIPTEXTUREID, srcRect, dstRect);
}

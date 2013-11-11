#include "ship_graphics_component.h"

#include <assert.h>
#include <string>

using namespace CapEngine;
using namespace std;

ShipGraphicsComponent::ShipGraphicsComponent(VideoManager* videoManagerIn){
  assert(videoManagerIn != nullptr);
  videoManager = videoManagerIn;
  string imageFile = "res/ship.png";
  surface = videoManager->loadImage(imageFile);
}

void ShipGraphicsComponent::render(GameObject* object){
  Rectangle rect = object->boundingPolygon();
  videoManager->drawSurface(rect.x, rect.y, surface);
}

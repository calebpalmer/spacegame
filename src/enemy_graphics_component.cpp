#include "enemy_graphics_component.h"

#include "locator.h"

using namespace CapEngine;

EnemyGraphicsComponent::EnemyGraphicsComponent(int textureId) : mTextureId(textureId) {}

void EnemyGraphicsComponent::render(GameObject* object) {
  AssetManager* assetManager = Locator::assetManager;

  Rectangle dstRect = object->boundingPolygon();

  Rectangle srcRect(0, 0, dstRect.width, dstRect.height);

  assetManager->draw(mTextureId, srcRect, dstRect);
}

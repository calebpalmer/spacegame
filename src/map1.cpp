#include "map1.h"
#include "locator.h"
#include "asset_constants.h"

#include <cassert>

using namespace CapEngine;

Map1::Map1() {}

void Map1::init(){
  width = 1200;
  height = 2400;
  y = height;
  velocity = 200;
 }

 Map1::~Map1() {}

 void Map1::update(real timestep){
   y -= velocity * (timestep / 1000.0);
   if( y < 0 ){
     y = height + y;
   }
 }

 void Map1::render(int screenWidth, int screenHeight){
   AssetManager* assetManager = Locator::assetManager;

   // whats left of map
   if(y - screenHeight < 0){
    int yStart = screenHeight - y;
    Rectangle srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.width = width;
    srcRect.height = y;

    Rectangle dstRect(0, 0, srcRect.width, srcRect.height);

    assetManager->draw(LEVEL1TEXTUREID, srcRect, dstRect);

    // start of the map again
    srcRect.y = height - (screenHeight - y);
    srcRect.height = screenHeight - y;

    dstRect.height = srcRect.height;

    assetManager->draw(LEVEL1TEXTUREID, srcRect, dstRect);



  }
  else{
    Rectangle srcRect;
    srcRect.x = 0;
    srcRect.y = y - screenHeight;
    srcRect.width = screenWidth;
    srcRect.height = screenHeight;

    Rectangle dstRect(0, 0, srcRect.width, srcRect.height);

    assetManager->draw(LEVEL1TEXTUREID, srcRect, dstRect);
  }
}

int Map1::getWidth(){
  return width;
}

int Map1::getHeight(){
  return height;
}

#ifndef LOCATOR_H
#define LOCATOR_H

#include "CapEngine.h"
#include "world.h"

class Locator{

 public:
  static CapEngine::VideoManager* videoManager;
  static CapEngine::Logger* logger;
  static CapEngine::SoundPlayer* soundPlayer;
  static CapEngine::Keyboard* keyboard;
  static CapEngine::AssetManager* assetManager;
  
  static World* world;
};

#endif

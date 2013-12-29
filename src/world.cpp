#include "world.h"

using namespace std;

World::~World(){
  // remove all objects in object collection
  vector<GameObject*>::iterator iter;
  for(iter = gameObjects.begin(); iter != gameObjects.end(); iter++){
    delete *iter;
  }
}

void World::addObject(GameObject& object){
  gameObjects.push_back(&object);
}

void World::removeObject(GameObject& object){
  // this is inefficient because it's O(n) searching for the element and O(n) re-arranging elements after deletion
  vector<GameObject*>::iterator iter = gameObjects.begin();
  while(iter != gameObjects.end()){
    if(*iter == &object){
      delete *iter;
      vector<GameObject*>::iterator tempIter = iter;
      iter = ++iter;
      iter = gameObjects.erase(tempIter, iter);
      continue;
    }
    iter++;
  }  
}

void World::update(double ms){
  vector<GameObject*>::iterator iter;
  for(iter = gameObjects.begin(); iter != gameObjects.end(); iter++){
    (*iter)->update(ms);
    // check for collisions with other objects
    // check for collisions with map
  }
}

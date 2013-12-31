#include "world.h"
#include "CapEngine.h"

using namespace std;
using namespace CapEngine;

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
    handleCollisions(**iter);

  }
}

vector<CollisionEvent> World::getCollisions(GameObject& object){
  vector<CollisionEvent> collisions;
  // // check for map collision
  CollisionType colType = detectMBRCollisionInterior(object.boundingPolygon(), Rectangle(0, 0, currentMap->width, currentMap->height));
  if(colType != COLLISION_NONE){
    CollisionEvent event;
    event.object1 = &object;
    event.object2 =nullptr;
    event.type = colType;
    event.class_ = COLLISION_WALL;
    collisions.push_back(event);
  }
  
  //check for inter-object collisions
  return collisions;  
}

void World::handleCollisions(GameObject& object){
  vector<CollisionEvent> collisions;
  collisions = getCollisions(object);
  if(collisions.size() != 0){
    vector<CollisionEvent>::iterator collisionIter;
    // for each collision
    for(collisionIter = collisions.begin(); collisionIter != collisions.end(); collisionIter++){
      object.handleCollision(collisionIter->type, collisionIter->class_, collisionIter->object2);
    }
  }
}

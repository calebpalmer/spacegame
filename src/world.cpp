#include "world.h"
#include "CapEngine.h"

#include <iostream>

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
  queuedObjects.push(&object);
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
  /**
     for each game object
         get collisions
	 for each collision
	     check to see if object can handle it
	     if object can handle it
	         detect collisions again
		 loop
	     else
	         world handles collision
		 if rollback to original object is needed
		     detect collisions again
     

  **/
  for(iter = gameObjects.begin(); iter != gameObjects.end(); iter++){ 
    unique_ptr<GameObject> newObject = (*iter)->update(ms);
    vector<CollisionEvent> collisions;
    collisions = getCollisions(*newObject);
    if(collisions.size() > 0){
      while(collisions.size() >  0){
#ifdef DEBUG
        cout << collisions.size() << " collisions detected. " << endl;
#endif
        bool handled = false;
        bool collisionsRecomputed = false;
        auto collisionIter = collisions.begin();
        while(collisionIter != collisions.end() && !collisionsRecomputed) {
	  handled = newObject->handleCollision(collisionIter->type, collisionIter->class_, collisionIter->object2);
	  if(handled){
	    *iter = newObject.release();
	    collisions = getCollisions(**iter);
	    collisionsRecomputed = true;
	  }
	  else{
	    bool rollback = false;
	    //// if collision event causes rollback
	    if(collisionIter->class_ == COLLISION_WALL){
	      if((*iter)->objectType != GameObject::Projectile){
		rollback=true;
	      }
	    }
      
	    if(rollback){
	      // leave *iter at the current object
	      collisions = getCollisions(**iter);
	      collisionsRecomputed = true;
	    }
	  }
	  collisionIter++;
        }  // for each collision
      }  // while collisions.size() != 0 
    } 

    else{
      *iter = newObject.release();
    }
  } 
  removeObsoleteObjects();
  addQueuedObjects();
}

vector<CollisionEvent> World::getCollisions(GameObject& object){
  vector<CollisionEvent> collisions;
  
// // check for map collision
  if(object.objectType != GameObject::Projectile){  // I want bullets to be able to pass out of the map and be cleaned up
    CollisionType colType = detectMBRCollisionInterior(object.boundingPolygon(), Rectangle(0, 0, currentMap->getWidth(), currentMap->getHeight()));
    if(colType != COLLISION_NONE){
      CollisionEvent event;
      event.object1 = &object;
      event.object2 =nullptr;
      event.type = colType;
      event.class_ = COLLISION_WALL;
      collisions.push_back(event);
#ifdef DEBUG
      cout << "collision added: type: " << (event.class_ == COLLISION_WALL ? "wall collision" : "other") << endl;
      if(event.class_ == COLLISION_WALL){
	cout << "object MBR: (" << object.boundingPolygon().x << "," << object.boundingPolygon().y << ") x (" << object.boundingPolygon().width
	     << "," << object.boundingPolygon().height << ")" << endl;
	cout << "Map MBR: (" << 0 << "," << 0 << ") x (" << currentMap->width
	     << "," << currentMap->height << ")" << endl;
      }
#endif
    
    }
  }
  
  //check for inter-object collisions

  return collisions;  
}

void World::removeObsoleteObjects(){
  vector<GameObject*>::iterator iter = gameObjects.begin();
  while(iter != gameObjects.end()){
    bool deleteObject = false;
    if((*iter)->objectType == GameObject::Projectile){
      // check if it is outside the map and delete if so
      if(MBRRelate((*iter)->boundingPolygon(), Rectangle(0, 0, currentMap->getWidth(), currentMap->getHeight())) == OUTSIDE){
	// delete object
	deleteObject = true;
      }
    }
    if(deleteObject){
      delete *iter;
      iter = gameObjects.erase(iter);
      // don't need to increment iterator because erase() already returns the next in the container.
    }
    else{
      iter++;
    }
  }  
}


void World::addQueuedObjects(){
  while(!queuedObjects.empty()){
    gameObjects.push_back(queuedObjects.front());
    queuedObjects.pop();
  }
  
}

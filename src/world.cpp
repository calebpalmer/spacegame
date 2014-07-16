#include "world.h"
#include "CapEngine.h"
#include "locator.h"

#include <iostream>
#include <sstream>

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
    if((*iter)->m_objectState != GameObject::Dead && (*iter)->m_objectState != GameObject::Inactive) {
      unique_ptr<GameObject> newObject = (*iter)->update(ms);
      vector<CollisionEvent> collisions;
      collisions = getCollisions(*newObject);
      if(collisions.size() > 0){
	while(collisions.size() >  0){
	  bool handled = false;
	  bool collisionsRecomputed = false;
	  auto collisionIter = collisions.begin();
	  while(collisionIter != collisions.end() && !collisionsRecomputed) {
	    handled = newObject->handleCollision(collisionIter->type, collisionIter->class_, collisionIter->object2);
	    if(handled){
	      *iter = newObject.release();
	      collisionIter = collisions.erase(collisionIter);
	      //collisions = getCollisions(**iter);
	      //collisionsRecomputed = true;
	    }
	    else{
	      bool rollback = false;
	      //// if collision event causes rollback
	      if(collisionIter->class_ == COLLISION_WALL){
		if((*iter)->objectType != GameObject::Projectile){
		  rollback=true;
		}
		if((*iter)->objectType == GameObject::Projectile){
		  (*iter)->m_objectState = GameObject::Dead;
		}

	      }
      
	      if(rollback){
		// leave *iter at the current object
		collisions = getCollisions(**iter);
		collisionsRecomputed = true;
	      }
	      collisionIter = collisions.erase(collisionIter);
	    }
	  }  // for each collision
	}  // while collisions.size() != 0 
      }// if(collisionss.size() > 0)  

      else{
	*iter = newObject.release();
      }
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
  // for each game object, only iterate the game objects after it
  auto otherObjectIter = gameObjects.begin();
  while(otherObjectIter != gameObjects.end()){
    if ((*otherObjectIter)->m_objectState != GameObject::Dead && (*otherObjectIter)->m_objectID != object.m_objectID ){
      // get bounding polygons for both objects
      Rectangle obj1MBR = object.boundingPolygon();
      Rectangle obj2MBR = (*otherObjectIter)->boundingPolygon();
      // if they intersect, create a CollisionEvent
      CollisionType colType = detectMBRCollision(obj1MBR, obj2MBR);
      if(colType != COLLISION_NONE){
	CollisionEvent colEvent;
	colEvent.object1 = &object;
	colEvent.object2 = *otherObjectIter;
	colEvent.type = colType;
	if((*otherObjectIter)->objectType == GameObject::Projectile){
	  colEvent.class_ = COLLISION_PROJECTILE;
	}
	else{
	  colEvent.class_ = COLLISION_ENTITY;
	}
	// append to collisions vector
	Locator::logger->log("Collision!", Logger::CDEBUG);
	collisions.push_back(colEvent);
      }
    }
    otherObjectIter++;
  }

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
    
    if((*iter)->m_objectState == GameObject::Dead || (*iter)->m_objectState == GameObject::Inactive){
      deleteObject = true;
    }

    if(deleteObject){
      ostringstream msg;
      msg << "Object " << (*iter)->m_objectID << " deleted";
      Locator::logger->log(msg.str(), Logger::CDEBUG);
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

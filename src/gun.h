#ifndef GUN_H
#define GUN_H

#include "gameobject.h"

#include <memory>

class Gun {
 public:
  virtual ~Gun() {};
  //virtual  Gun& operator=(const Gun& src);
  virtual std::unique_ptr<Gun> clone() const = 0;
  virtual void fire(int x, int y, ObjectID parentID) = 0;
  virtual int ammoRemaining() = 0;
};

#endif // GUN_H

#ifndef GAMEOBJECT_GAMEOBJECT_H_
#define GAMEOBJECT_GAMEOBJECT_H_

#include "Model/Coordinate.h"

class QPainter;

class GameObject {
 public:
  virtual void Draw(QPainter*) = 0;
  virtual void Tick() = 0;

 protected:
  Coordinate position_;
};

#endif  // GAMEOBJECT_GAMEOBJECT_H_

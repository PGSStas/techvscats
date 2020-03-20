#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>
#include "Model/Coordinate.h"

class GameObject {
 public:
  virtual void Draw(QPainter*) = 0;
  virtual void Tick() = 0;

 protected:
  Coordinate position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

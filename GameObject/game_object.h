#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>
#include "Model/coordinate.h"

class GameObject {
 public:

  virtual void Draw(QPainter*) const = 0;
  virtual void Tick(int current_time) = 0;
  Coordinate GetPosition() const;
  void SetPosition(const Coordinate& position);
 private:
  Coordinate position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

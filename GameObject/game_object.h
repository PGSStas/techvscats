#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>
#include "Model/coordinate.h"

class GameObject {
 public:
  GameObject() = default;
  virtual void Draw(QPainter*) const = 0;
  virtual void Tick() = 0;
  Coordinate GetPosition() const;
  void SetPosition(const Coordinate& position);

 protected:
  Coordinate position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

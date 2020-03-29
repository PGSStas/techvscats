#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>

#include "Model/coordinate.h"

class GameObject {
 public:
  GameObject() = default;
  explicit GameObject(Coordinate position);

  virtual void Draw(QPainter* painter) const = 0;
  virtual void Tick(int current_time) = 0;

  Coordinate GetPosition() const;
  void SetPosition(Coordinate position);

 protected:
  int object_current_time_ = 0;
  Coordinate position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

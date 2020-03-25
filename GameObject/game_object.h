#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>

#include "Model/coordinate.h"

class GameObject {
 public:
  GameObject() = default;
  explicit GameObject(Coordinate pos);

  virtual void Draw(QPainter* p) const = 0;
  virtual void Tick() = 0;

  Coordinate GetPosition() const;
  void SetPosition(Coordinate pos);

 protected:
  Coordinate position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

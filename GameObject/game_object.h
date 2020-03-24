#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>
#include <memory>
#include "Model/coordinate.h"
#include "View/size_handler.h"

class GameObject {
 public:
  GameObject() = default;

  virtual void Draw(QPainter*, std::shared_ptr<SizeHandler>) const = 0;
  virtual void Tick() = 0;

  Coordinate GetPosition() const;

 protected:
  Coordinate position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

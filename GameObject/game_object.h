#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <memory>
#include <QPainter>

#include "Model/coordinate.h"
#include "Model/size.h"
#include "View/size_handler.h"

class GameObject {
 public:
  GameObject() = default;
  explicit GameObject(Coordinate position);

  virtual void Draw(QPainter* painter, std::shared_ptr<SizeHandler>) const = 0;
  virtual void Tick() = 0;

  Coordinate GetPosition() const;
  void SetPosition(Coordinate position);
  Size GetSize() const;

 protected:
  Coordinate position_;
  Size size_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

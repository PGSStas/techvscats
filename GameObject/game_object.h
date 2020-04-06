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

  virtual void Draw(QPainter* painter,
                    const SizeHandler& size_handler) const = 0;
  virtual void Tick(int current_time) = 0;

  Coordinate GetPosition() const;
  void SetPosition(Coordinate position);
  Size GetSize() const;

 protected:
  int object_current_time_ = 0;
  Coordinate position_;
  Size size_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

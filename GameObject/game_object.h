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
  GameObject(Coordinate position, Size size);

  virtual void Draw(QPainter* painter,
      const std::shared_ptr<SizeHandler>& size_handler) const = 0;
  virtual void Tick(int time) = 0;

  Coordinate GetPosition() const;
  void SetPosition(Coordinate position);
  Size GetSize() const;
  void SetSize(Size size);

 protected:
  Coordinate position_;
  Size size_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

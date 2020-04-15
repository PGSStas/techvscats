#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <algorithm>
#include <memory>
#include <QPainter>

#include "Model/coordinate.h"
#include "Model/size.h"
#include "View/size_handler.h"

class GameObject {
 public:
  explicit GameObject(Size size, Coordinate position = {0, 0});

  virtual void Tick(int current_time) = 0;
  void UpdateTime(int current_time);
  virtual void  Draw(QPainter* painter,
                    const SizeHandler& size_handler) const = 0;

  void SetPosition(Coordinate position);
  Coordinate GetPosition() const;
  Size GetSize() const;

 protected:
  int delta_tick_time_ = 0;
  int object_life_time_ = 0;
  Size size_;
  Coordinate position_;

 private:
  int object_last_time_ = 0;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_

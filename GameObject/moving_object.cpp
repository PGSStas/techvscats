#include "moving_object.h"

MovingObject::MovingObject(Size size, double speed,
                           Coordinate position, Coordinate destination)
    : GameObject(size, position),
      speed_(speed), destination_(destination) {}

bool MovingObject::IsEndReached() const {
  return is_end_reached_;
}

bool MovingObject::IsDead() const {
  return is_dead_;
}
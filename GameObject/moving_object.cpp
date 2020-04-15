#include "moving_object.h"

MovingObject::MovingObject(double speed) : speed_(speed) {}

bool MovingObject::IsEndReached() const {
  return is_end_reached_;
}

double MovingObject::GetSpeed() const {
  return speed_;
}

bool MovingObject::IsDead() const {
  return is_dead_;
}

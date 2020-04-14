#include "moving_object.h"

bool MovingObject::HasReached() const {
  return is_end_reached_;
}

double MovingObject::GetSpeed() const {
  return speed_;
}

bool MovingObject::IsDead() const {
  return is_dead_;
}

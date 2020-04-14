#include "moving_object.h"

void MovingObject::SetSpeedCoefficient(double speed_coefficient) {
  speed_coefficient_ = speed_coefficient;
}

bool MovingObject::HasReached() const {
  return has_reached_;
}

double MovingObject::GetSpeed() const {
  return speed_ * speed_coefficient_;
}

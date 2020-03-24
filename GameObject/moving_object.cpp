#include "moving_object.h"

void MovingObject::SetSpeedCoefficient(double speed_coefficient) {
  speed_coefficient_ = speed_coefficient;
}

bool MovingObject::HasReached() const {
  return has_reached_;
}

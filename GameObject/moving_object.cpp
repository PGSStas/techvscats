#include "moving_object.h"

MovingObject::MovingObject(double speed) : speed_(speed){}

bool MovingObject::IsEndReached() const {
  return is_end_reached_;
}

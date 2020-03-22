#include "moving_object.h"

double MovingObject::GetSpeed() const {
  return speed_;
}

void MovingObject::SetSpeed(double speed) {
  speed_ = speed;
}

Coordinate MovingObject::GetDestination() const {
  return destination_;
}

bool MovingObject::GetIsReached() const {
  return has_reached_;
}

void MovingObject::SetHasReached(bool is_reached) {
  has_reached_ = is_readned;
}

void MovingObject::SetDestination(const Coordinate& destination) {
  destination_ = destination;
}


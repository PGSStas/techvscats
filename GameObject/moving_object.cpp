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
  return is_reached_destination_;
}

void MovingObject::SetIsReached(bool is_reached) {
  is_reached_destination_ = is_reached;
}

void MovingObject::SetDestination(const Coordinate& destination) {
  destination_ = destination;
}


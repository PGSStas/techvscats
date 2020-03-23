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

bool MovingObject::HasReached() const {
  return has_reached_;
}

void MovingObject::SetHasReached(bool has_reached) {
  has_reached_ = has_reached;
}

void MovingObject::SetDestination(const Coordinate& destination) {
  destination_ = destination;
}

MovingObject::MovingObject(const Coordinate& start_position,
                           const Coordinate& destination,
                           double speed, double speed_coefficient)
    : GameObject(start_position), destination_(destination),
      speed_(speed), speed_coefficient_(speed_coefficient) {}


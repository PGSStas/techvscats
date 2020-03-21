#include "moving_object.h"

void MovingObject::Move() {
  Coordinate position = GetPosition();
  // to update
  Coordinate move = {1, 1};
  position += move;
  SetPosition(position);
}

void MovingObject::SetDestination(const Coordinate& destination) {
  destination_ = destination;
}

double MovingObject::GetSpeed() const {
  return speed_;
}

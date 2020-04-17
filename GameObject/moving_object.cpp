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

void MovingObject::MoveToDestination() {
  Size move_direction = position_.GetVectorTo(destination_);

  if (move_direction.GetLength() > kEpsilon) {
    move_direction /= move_direction.GetLength();
    move_direction *= delta_tick_time_ * speed_ / kTimeScale;
  }
  if ((position_ + move_direction).GetVectorTo(destination_).width
      * position_.GetVectorTo(destination_).width <= 0) {
    position_ = destination_;
  } else {
    position_ += move_direction;
  }
}


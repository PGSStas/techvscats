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

  if (move_direction.GetLength() > constants::kEpsilon) {
    move_direction /= move_direction.GetLength();
    move_direction *= delta_time_ * speed_ / constants::kTimeScale;
  }
  auto first_vector = (position_ + move_direction).GetVectorTo(destination_);
  auto second_vector = position_.GetVectorTo(destination_);
  if (first_vector.width * second_vector.width <= constants::kEpsilon &&
      first_vector.height * second_vector.height <= constants::kEpsilon) {
    position_ = destination_;
  } else {
    position_ += move_direction;
  }
}

void MovingObject::SetSpeed(double speed) {
  speed_ = speed;
}
double MovingObject::GetSpeed() const {
  return speed_;
}

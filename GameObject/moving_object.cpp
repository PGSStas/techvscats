#include "moving_object.h"


void MovingObject::SetDestination(const Coordinate& destination) {
  destination_ = destination;
}

double MovingObject::GetSpeed() const {
  return speed_;
}

void MovingObject::SetSpeed(double speed) {
  speed_ = speed;
}

int MovingObject::GetLiveTime() const {
  return current_time_ - start_live_time_;
}

void MovingObject::SetStartLiveTime(int current_time) {
  start_live_time_ = current_time;
}

void MovingObject::SetCurrentTime(int current_time) {
  current_time_ = current_time;
}

Coordinate MovingObject::GetDestination() const {
  return destination_;
}

bool MovingObject::GetIsReached() {
  return is_reached_destination_;
}

void MovingObject::SetIsReached(bool is_reached) {
  is_reached_destination_ = is_reached;
}


#include "game_object.h"

void GameObject::UpdateTime(int current_time) {
  if (object_last_time_ != 0) {
    delta_tick_time_=current_time - object_last_time_;
    object_life_time_ += delta_tick_time_;
  }
  object_last_time_ = current_time;
}

Coordinate GameObject::GetPosition() const {
  return position_;
}

void GameObject::SetPosition(Coordinate position) {
  position_ = position;
}

Size GameObject::GetSize() const {
  return size_;
}

#include "game_object.h"

GameObject::GameObject(Size size, Coordinate position)
    : size_(size), position_(position) {
}

void GameObject::UpdateTime(int current_time) {
  if (object_last_time_ != 0) {
    delta_tick_time_ = current_time - object_last_time_;
    object_life_time_ += delta_tick_time_;
  }
  object_last_time_ = current_time;
}

void GameObject::SetPosition(Coordinate position) {
  position_ = position;
}

void GameObject::SetAnimationParameters(
    const std::vector<std::shared_ptr<std::vector<QImage>>>& animation_images_,
    const std::vector<int>& action_time) {
  for (int i = 0; i < action_time.size(); i++) {
    animation_players_.emplace_back(animation_images_[i], action_time[i]);
  }
}

void GameObject::Rescale(Size to_size) {
  for (auto& player : animation_players_) {
    player.Rescale(to_size);
  }
}

Coordinate GameObject::GetPosition() const {
  return position_;
}

Size GameObject::GetSize() const {
  return size_;
}

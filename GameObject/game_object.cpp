#include "game_object.h"

GameObject::GameObject(Size size, Coordinate position)
    : size_(size), position_(position), particle_handler_(size_, position_) {
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

void GameObject::SetAnimationPlayers(
    const std::vector<AnimationPlayer>& animation_players) {
  animation_players_ = animation_players;
  if (animation_players_.empty()) {
    animation_players_.resize(3, AnimationPlayer(
        std::make_shared<std::vector<QImage>>(
            1, QImage(":resources/images/error.png"))));

  }
  action_timings_.clear();
  for (const auto& animation_player : animation_players_) {
    action_timings_.push_back(animation_player.GetAnimationDuration());
  }
}

void GameObject::Rescale(Size to_size) {
  for (auto& player : animation_players_) {
    player.Rescale(to_size);
  }
  if (animation_players_.empty()) {
    SetAnimationPlayers(animation_players_);
  }
}

Coordinate GameObject::GetPosition() const {
  return position_;
}

ParticleHandler* GameObject::GetParticleHandler() {
  return &particle_handler_;
}

Size GameObject::GetSize() const {
  return size_;
}

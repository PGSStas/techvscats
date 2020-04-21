#include "game_object.h"

GameObject::GameObject(Size size, Coordinate position)
    : size_(size), position_(position), particle_handler(size_, position_) {
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
  for (const auto& animation_player: animation_players_) {
    action_timings_.push_back(animation_player.GetAnimationDuration());
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

ParticleHandler* GameObject::GetParticleHandler() {
  return &particle_handler;
}

Size GameObject::GetSize() const {
  return size_;
}

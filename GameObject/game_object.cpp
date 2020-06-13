#include "game_object.h"

GameObject::GameObject(Size size, Coordinate position)
    : size_(size), position_(position),
      particle_handler_(size_, position_, delta_time_) {
}

void GameObject::UpdateTime(int current_time) {
  if (object_last_time_ != 0) {
    delta_time_ = current_time - object_last_time_;
    object_life_time_ += delta_time_;
  }
  object_last_time_ = current_time;
}

void GameObject::SetPosition(Coordinate position) {
  position_ = position;
}

void GameObject::SetAnimationPlayers(
    std::vector<AnimationPlayer> animation_players) {
  animation_players_ = std::move(animation_players);
  action_timings_.clear();
  for (const auto& animation_player : animation_players_) {
    action_timings_.push_back(animation_player.GetAnimationDuration());
  }
}

void GameObject::SetDrawingAttitude(Size attitude) {
  drawing_attitude_ = attitude;
}

void GameObject::Rescale(Size to_size) {
  for (auto& player : animation_players_) {
    player.Rescale(to_size);
  }
}

Coordinate GameObject::GetPosition() const {
  return position_;
}

Coordinate GameObject::GetPositionWithAttitude() const {
  return position_ + size_ * drawing_attitude_;
}

ParticleHandler* GameObject::GetParticleHandler() {
  return &particle_handler_;
}

Size GameObject::GetSize() const {
  return size_;
}

void GameObject::SetSize(Size size) {
  size_ = size;
}

#include "particle.h"

#include <utility>

Particle::Particle(Size size, int repeat_number)
    : GameObject(size), repeat_number_(repeat_number) {
}

Particle::Particle(const Particle& other)
    : Particle(other.size_, other.repeat_number_) {
  SetAnimationPlayers(other.animation_players_);
  SetSoundId(sound_id_);
}

void Particle::Tick(int current_time) {
  UpdateTime(current_time);
  animation_players_[0].Tick(delta_time_);
  time_to_death_ -= delta_time_;
  if (time_to_death_ <= 0) {
    is_dead_ = true;
  }
}

void Particle::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  Coordinate point;
  point = size_handler.GameToWindowCoordinate(position_ - size_ / 2);

  painter->translate(point.x, point.y);
  painter->drawImage(0, 0, animation_players_[0].GetCurrentFrame());

  painter->restore();
}

void Particle::SetIfEmpty(Size size, Coordinate position,
                          int repeat_number) {
  if (size_ == Size(-1, -1)) {
    size_ = size;
  }
  position_ = position;
  if (repeat_number_ == -1) {
    repeat_number_ = repeat_number;
  }
  time_to_death_ = animation_players_[0].GetAnimationDuration()
      * repeat_number_ * kLifetimeOffset;
}

bool Particle::IsDead() const {
  return is_dead_;
}

void Particle::SetSoundId(int id) {
  sound_id_ = id;
}

int Particle::GetSoundId() const {
  return sound_id_;
}

#include "particle.h"

#include <utility>

Particle::Particle(Size size, int repeat_number, double speed,
                   Size look_direction) :
    MovingObject(size, speed), look_direction_(look_direction),
    repeat_number_(repeat_number) {
}

Particle::Particle(const Particle& other) :
    Particle(other.size_, other.repeat_number_,
             other.speed_, other.look_direction_) {
  SetAnimationPlayers(other.animation_players_);
}

void Particle::Tick(int current_time) {
  UpdateTime(current_time);
  animation_players_[0].Tick(delta_tick_time_);
  time_to_death_ -= delta_tick_time_;
  if (time_to_death_ <= 0) {
    is_dead_ = true;
  }
}

void Particle::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  Coordinate point =
      size_handler.GameToWindowCoordinate(position_ - size_ / 2);
  Size size = size_handler.GameToWindowSize(size_);

  painter->translate(point.x, point.y);
  // look direction set !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  painter->drawImage(QRect(0, 0, size.width, size.height),
                     animation_players_[0].GetCurrentFrame());

  painter->restore();
}

void Particle::SetParameters(Size size, Coordinate position, int repeat_number,
                             Size look_direction, double speed) {
  if (size_ == Size(-1, -1)) {
    size_ = size;
  }
  position_ = position;
  if (look_direction == Size(-1, -1)) {
    look_direction_ = look_direction;
    speed_ = speed;
  }
  if (repeat_number == -1) {
    repeat_number_ = repeat_number;
  }
  if (repeat_number_ == -1) {
    repeat_number_ = repeat_number;
  }
  time_to_death_ = animation_players_[0].GetAnimationDuration()
      * repeat_number_;
}

void Particle::Move() {
  destination_ = position_ + look_direction_;
  MoveToDestination(false);
}



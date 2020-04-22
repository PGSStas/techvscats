#include "particle.h"

#include <utility>

Particle::Particle(Size size, double speed, Size look_direction) :
    MovingObject(size, speed), look_direction_(look_direction) {}

Particle::Particle(const Particle& other) :
    MovingObject(other.GetSize(), other.speed_),
    look_direction_(other.look_direction_) {
  SetAnimationPlayers(other.animation_players_);
}

void Particle::Tick(int current_time) {
  UpdateTime(current_time);
  animation_players_[0].Tick(current_time);
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

void Particle::SetParameters(
    Coordinate position, Size look_direction, double speed) {
  position_ = position;
  if (look_direction != Size(-1, -1)) {
    look_direction_ = look_direction;
    speed_ = speed;
  }
}

void Particle::Move() {

}



#include "particle.h"

#include <utility>

void Particle::Tick(int current_time) {
  UpdateTime(current_time);
  animation_player_.Tick(current_time);
}

void Particle::Draw(QPainter* painter, const SizeHandler& size_handler) const {
  painter->save();

  Coordinate point =
      size_handler.GameToWindowCoordinate(position_ - size_ / 2);
  Size size = size_handler.GameToWindowSize(size_);

  painter->translate(point.x, point.y);
  // look direction set !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  painter->drawImage(QRect(0, 0, size.width, size.height),
                     animation_player_.GetCurrentFrame());

  painter->restore();
}

Particle::Particle(int life_time, AnimationPlayer animation_player,
                   Size size, Coordinate position, Size look_direction,
                   double speed) :
    MovingObject(size, speed, position), look_direction_(look_direction),
    life_time_(life_time),animation_player_(std::move(animation_player)) {}

void Particle::Move() {

}



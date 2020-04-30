#include "laser_projectile.h"

LaserProjectile::LaserProjectile(Size size) :
    AbstractProjectile(size, 0) {}

void LaserProjectile::Tick(int current_time) {
  UpdateTime(current_time);
  animation_players_[0].Tick(delta_time_);
  if (object_life_time_ > action_timings_[0] || aim_->IsDead()) {
    position_ = aim_->GetPosition();
    particle_handler_.CarrierDeath();
    is_end_reached_ = true;
    is_dead_ = true;
  }
}

void LaserProjectile::Draw(QPainter* painter,
                           const SizeHandler& handler) const {
  painter->save();
  Coordinate end_position = handler.GameToWindowCoordinate(aim_->GetPosition());
  Coordinate start_position = handler.GameToWindowCoordinate(position_);
  Size size = handler.GameToWindowSize(size_);
  painter->setPen(QPen(QBrush(animation_players_[0].GetCurrentFrame()),
                       size.width /10));
  painter->drawLine(start_position.x, start_position.y,
                    end_position.x, end_position.y);
  painter->restore();
}

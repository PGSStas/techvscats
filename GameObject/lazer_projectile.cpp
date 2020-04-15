#include "lazer_projectile.h"

void LazerProjectile::Draw(QPainter* painter,
                           const SizeHandler& handler) const {
  painter->save();
  Coordinate end_position = handler.GameToWindowCoordinate(aim_->GetPosition());
  Coordinate start_position = handler.GameToWindowCoordinate(start_position_);
  Size size = handler.GameToWindowSize(size_);
  painter->setPen(QPen(draw_color_, size.width));
  painter->drawLine(start_position.x, start_position.y,
                    end_position.x, end_position.y);
  painter->restore();
}

void LazerProjectile::Tick(int current_time) {
  if (object_time_ == 0) {
    object_time_ = current_time;
  }
  if (current_time - object_time_ > iteration_time_ || aim_->IsDead()) {
    position_ = aim_->GetPosition();
    has_reached_ = true;
    is_dead_ = true;
  }
}

LazerProjectile::LazerProjectile(const Projectile& other) : Projectile(other) {
  start_position_ = position_;
}

LazerProjectile::LazerProjectile(Size size,
                                 double speed,
                                 ProjectileType projectile_type) :
    Projectile(size, speed, projectile_type) {}

#include "lazer_projectile.h"

LazerProjectile::LazerProjectile(const AbstractProjectile& other) : AbstractProjectile(other) {}

LazerProjectile::LazerProjectile(Size size,
                                 ProjectileType projectile_type) :
    AbstractProjectile(size, 0, projectile_type) {}

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
  UpdateTime(current_time);
  if (object_life_time_ > iteration_time_ || aim_->IsDead()) {
    position_ = aim_->GetPosition();
    is_end_reached_ = true;
    is_dead_ = true;
  }
}

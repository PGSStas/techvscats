#include "homing_projectile.h"

HomingProjectile::HomingProjectile(Size size, double speed)
    : AbstractProjectile(size, speed) {}

void HomingProjectile::Tick(int current_time) {
  UpdateTime(current_time);
  destination_ = aim_->GetPosition();
  Move();
  animation_players_[0].Tick(delta_time_);
}

void HomingProjectile::Draw(QPainter* painter,
                            const SizeHandler& handler) const {
  painter->save();
  Coordinate point = handler.GameToWindowCoordinate(
      position_ - size_ / 2);

  painter->drawPixmap(point.x, point.y, animation_players_[0].GetCurrentFrame());

  painter->restore();
}

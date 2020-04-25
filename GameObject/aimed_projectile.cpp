#include "aimed_projectile.h"

AimedProjectile::AimedProjectile(Size size, double speed)
    : AbstractProjectile(size, speed) {}

void AimedProjectile::Tick(int current_time) {
  UpdateTime(current_time);
  destination_ = aim_->GetPosition();
  Move();
  animation_players_[0].Tick(delta_time_);
}

void AimedProjectile::Draw(QPainter* painter,
                           const SizeHandler& handler) const {
  painter->save();
  Coordinate point = handler.GameToWindowCoordinate(
      position_ - size_ / 2);

  painter->translate(point.x, point.y);
  painter->drawImage(QPoint(0, 0), animation_players_[0].GetCurrentFrame());

  painter->restore();
}

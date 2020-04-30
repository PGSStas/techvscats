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

  painter->drawImage(point.x, point.y, animation_players_[0].GetCurrentFrame());

  painter->restore();
}

#include "aimed_projectile.h"

AimedProjectile::AimedProjectile(Size size, double speed, ProjectileType type)
    : AbstractProjectile(size, speed, type) {}

AimedProjectile::AimedProjectile(const AbstractProjectile& other)
    : AbstractProjectile(other) {}

void AimedProjectile::Draw(QPainter* painter,
                           const SizeHandler& handler) const {
  painter->save();
  painter->setBrush(draw_color_);
  Coordinate position = handler.GameToWindowCoordinate(position_);
  Size size = handler.GameToWindowSize(size_);
  painter->drawEllipse(position.x, position.y, size.width, size.height);
  painter->restore();
}

void AimedProjectile::Tick(int current_time) {
  UpdateTime(current_time);
  destination_ = aim_->GetPosition();
  Move();
}

#include "aimed_projectile.h"

AimedProjectile::AimedProjectile(const AimedProjectile& other)
    : AbstractProjectile(other) {}

AimedProjectile::AimedProjectile(Size size, double speed)
    : AbstractProjectile(size, speed) {}

void AimedProjectile::Tick(int current_time) {
  UpdateTime(current_time);
  destination_ = aim_->GetPosition();
  Move();
}

void AimedProjectile::Draw(QPainter* painter,
                           const SizeHandler& handler) const {
  painter->save();
  painter->setBrush(draw_color_);
  Coordinate position = handler.GameToWindowCoordinate(position_);
  Size size = handler.GameToWindowSize(size_);
  painter->drawEllipse(position.x, position.y, size.width, size.height);
  painter->restore();
}

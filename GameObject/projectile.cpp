#include "projectile.h"
Projectile::Projectile(Size size, double speed, ProjectileType type)
    : type_(type) {
  speed_ = speed;
  size_ = size;
}

void Projectile::SetParameters(double speed, int damage,
                               std::shared_ptr<Enemy> aim) {
  damage_ = damage;
  speed_ = speed;
  aim_ = aim;
}

void Projectile::SetAnimationParameters(QColor draw_color) {
  draw_color_ = draw_color;
}

Projectile::Projectile(const Projectile& other) {
  SetParameters(other.speed_, other.damage_, other.aim_);
  SetAnimationParameters(other.draw_color_);
  position_ = other.position_;
  size_ = other.size_;
}

void Projectile::Draw(QPainter* painter, const SizeHandler& handler) const {
  painter->save();
  painter->setBrush(draw_color_);
  Coordinate position = handler.GameToWindowCoordinate(position_);
  Size size = handler.GameToWindowSize(size_);
  painter->drawEllipse(position.x, position.y, size.width, size.height);
  painter->restore();
}

void Projectile::Tick(int current_time) {
  Move();
}

void Projectile::Move() {
  destination_ = aim_->GetPosition();
  position_ += position_.GetDistanceTo(destination_) /=
      position_.GetDistanceTo(destination_).GetLength() / speed_;
  if (position_.GetDistanceTo(aim_->GetPosition()).GetLength() < 10) {
    is_dead_ = true;
  }
}

ProjectileType Projectile::GetType() const {
  return type_;
}

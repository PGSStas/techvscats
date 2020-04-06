#include "projectile.h"
Projectile::Projectile(ProjectileType type)
    : type_(type) {

}

void Projectile::SetParameters(int speed, int damage,
                               std::shared_ptr<Enemy> aim) {
  damage_ = damage;
  speed_ = speed;
  aim_ = aim;
}

void Projectile::SetAnimationParameters(QColor draw_color,
                                        int projectile_size) {
  draw_color_ = draw_color;
  projectile_size_ = projectile_size;
}

Projectile::Projectile(const std::shared_ptr<Projectile>& other) {
  SetParameters(other->damage_, other->speed_, other->aim_);
  SetAnimationParameters(other->draw_color_, other->projectile_size_);
}

void Projectile::Draw(QPainter* painter) const {
  painter->save();
  painter->setBrush(draw_color_);
  painter->drawEllipse(QPoint(position_.x, position_.y),
                       projectile_size_,
                       projectile_size_);
  painter->restore();
}

void Projectile::Tick(int current_time) {
  Move();
}

void Projectile::Move() {
  destination_ = aim_->GetPosition();
  position_ += position_.GetBetween(destination_) /=
      position_.GetBetween(destination_).GetLength() / speed_;
  if (position_.GetBetween(aim_->GetPosition()).GetLength() < 10) {
    is_dead_ = true;
  }
}

ProjectileType Projectile::GetType() const {
  return type_;
}

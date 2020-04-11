#include "projectile.h"
Projectile::Projectile(Size size, double speed, ProjectileType type)
    : type_(type) {
  speed_ = speed;
  size_ = size;
}

void Projectile::SetParameters(double speed, double damage,
                               std::shared_ptr<Enemy> aim) {
  speed_ = speed;
  damage_ = damage;
  aim_ = aim;
  if (aim != nullptr) {
    destination_ = aim->GetPosition();
  }
}

void Projectile::SetAnimationParameters(QColor draw_color, int iteration_time) {
  draw_color_ = draw_color;
  iteration_time_ = iteration_time;
}

Projectile::Projectile(const Projectile& other) {
  SetAnimationParameters(other.draw_color_, other.iteration_time_);
  SetParameters(other.speed_, other.damage_, other.aim_);

  position_ = other.position_;
  effect_radius_ = other.effect_radius_;
  type_ = other.type_;
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
  destination_ = aim_->GetPosition();
  Move();
}

void Projectile::Move() {
  Size move = position_.GetDistanceTo(destination_) /=
                  position_.GetDistanceTo(destination_).GetLength() / speed_;

  if ((position_ + move).GetDistanceTo(destination_).width
      * position_.GetDistanceTo(destination_).width <= 0) {
    position_ = destination_;
  } else {
    position_ += move;
  }

  if (position_.GetDistanceTo(destination_).GetLength() < kEpsilon) {
    has_reached_ = true;
    is_dead_ = true;
  }
}

ProjectileType Projectile::GetType() const {
  return type_;
}

bool Projectile::IsInAffectedArea(const Enemy& enemy) {
  return enemy.GetPosition() == aim_->GetPosition();
}

double Projectile::GetDamage() const {
  return damage_;
}

void Projectile::SetType(ProjectileType type) {
  type_ = type;
}

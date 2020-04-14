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
  type_ = other.type_;
  size_ = other.size_;

  up_force_ = other.up_force_;
  start_position_ = position_;
  effect_radius_ = other.effect_radius_;
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
  UpdateTime(current_time);
  destination_ = aim_->GetPosition();
  Move();
}

void Projectile::Move() {
  position_.MoveTo(destination_, delta_tick_time_ *
      speed_ / kTimeScale);
  if (position_ == destination_) {
    is_end_reached_ = true;
    is_dead_ = true;
  }
}

ProjectileType Projectile::GetType() const {
  return type_;
}

bool Projectile::IsInAffectedArea(const Enemy& enemy) {
  return position_.GetVectorTo(enemy.GetPosition()).GetLength()
      <= effect_radius_ + kEpsilon;
}

double Projectile::GetDamage() const {
  return damage_;
}

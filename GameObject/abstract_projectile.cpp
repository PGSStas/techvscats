#include "abstract_projectile.h"


AbstractProjectile::AbstractProjectile(
    Size size, double speed, ProjectileType type,
    double effect_radius, double up_force)
    : MovingObject(size, speed), type_(type),
    effect_radius_(effect_radius),up_force_(up_force) {}

AbstractProjectile::AbstractProjectile(const AbstractProjectile& other) :
    MovingObject(other.size_, 0, other.position_), type_(other.type_),
    effect_radius_(other.effect_radius_), up_force_(other.up_force_),
    start_position_(position_) {
  SetAnimationParameters(other.draw_color_, other.iteration_time_);
  SetParameters(other.position_, other.speed_, other.damage_, other.aim_);
}

void AbstractProjectile::SetParameters(
    Coordinate position, double speed, double damage,
   const std::shared_ptr<Enemy>& aim) {
  position_ = position;
  start_position_ = position_;
  speed_ = speed;
  damage_ = damage;
  aim_ = aim;
  if (aim != nullptr) {
    destination_ = aim->GetPosition();
  }
}

void AbstractProjectile::SetAnimationParameters(QColor draw_color,
                                                int iteration_time) {
  draw_color_ = std::move(draw_color);
  iteration_time_ = iteration_time;
}

void AbstractProjectile::Move() {
  position_.MoveTo(destination_, delta_tick_time_ *
      speed_ / kTimeScale);
  if (position_ == destination_) {
    is_end_reached_ = true;
    is_dead_ = true;
  }
}

ProjectileType AbstractProjectile::GetType() const {
  return type_;
}

bool AbstractProjectile::IsInAffectedArea(const Enemy& enemy) {
  return position_.GetVectorTo(enemy.GetPosition()).GetLength()
      <= effect_radius_ + kEpsilon;
}

double AbstractProjectile::GetDamage() const {
  return damage_;
}

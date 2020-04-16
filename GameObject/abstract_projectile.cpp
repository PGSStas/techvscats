#include "abstract_projectile.h"

AbstractProjectile::AbstractProjectile(Size size, double speed)
    : MovingObject(size, speed) {}

AbstractProjectile::AbstractProjectile(const AbstractProjectile& other) :
    MovingObject(other.size_, other.speed_, other.position_) {
  SetAnimationParameters(other.draw_color_, other.iteration_time_);
}

void AbstractProjectile::Move() {
  MoveToDestination();
  if (position_ == destination_) {
    is_end_reached_ = true;
    is_dead_ = true;
  }
}

void AbstractProjectile::SetParameters(
    const std::shared_ptr<Enemy>& aim, Coordinate position,
    double speed_coefficient, double damage) {
  aim_ = aim;
  position_ = position;
  speed_ = speed_ * speed_coefficient;
  damage_ = damage;
  if (aim != nullptr) {
    destination_ = aim->GetPosition();
  }
}

void AbstractProjectile::SetAnimationParameters(
    const QColor& draw_color, int iteration_time) {
  draw_color_ = draw_color;
  iteration_time_ = iteration_time;
}

bool AbstractProjectile::IsInAffectedArea(const Enemy& enemy) {
  return position_.GetVectorTo(enemy.GetPosition()).GetLength()
      <= kEpsilon;
}

double AbstractProjectile::GetDamage() const {
  return damage_;
}


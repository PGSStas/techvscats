#include "abstract_projectile.h"

AbstractProjectile::AbstractProjectile(const AbstractProjectile& other) :
    MovingObject(other.size_, other.speed_, other.position_) {
  SetAnimationParameters(other.draw_color_, other.iteration_time_);
}

AbstractProjectile::AbstractProjectile(Size size, double speed)
    : MovingObject(size, speed){}

void AbstractProjectile::SetParameters(
    Coordinate position, double speed_coefficient, double damage,
    const std::shared_ptr<Enemy>& aim) {
  position_ = position;
  speed_ = speed_ * speed_coefficient;
  damage_ = damage;
  aim_ = aim;
  if (aim != nullptr) {
    destination_ = aim->GetPosition();
  }
}

void AbstractProjectile::SetAnimationParameters(
    QColor draw_color, int iteration_time) {
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

 bool AbstractProjectile::IsInAffectedArea(const Enemy& enemy) {
  return position_.GetVectorTo(enemy.GetPosition()).GetLength()
      <=  kEpsilon;
}

double AbstractProjectile::GetDamage() const {
  return damage_;
}
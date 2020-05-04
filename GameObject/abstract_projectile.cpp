#include "abstract_projectile.h"

AbstractProjectile::AbstractProjectile(Size size, double speed)
    : MovingObject(size, speed) {}

AbstractProjectile::AbstractProjectile(const AbstractProjectile& other) :
    MovingObject(other.size_, other.speed_, other.position_) {
  SetAnimationPlayers(other.animation_players_);
  particle_handler_.SetParticlePacks(other.particle_handler_);
}

void AbstractProjectile::Move() {
  MoveToDestination();
  if (position_ == destination_) {
    particle_handler_.PlayOwnerDeath();
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

double AbstractProjectile::GetDamage() const {
  return damage_;
}

bool AbstractProjectile::IsInAffectedArea(const Enemy& enemy) {
  return position_.GetVectorTo(enemy.GetPosition()).GetLength()
      <= constants::kEpsilon;
}


ProjectileType AbstractProjectile::GetProjectileType() {
  return projectile_type;
}

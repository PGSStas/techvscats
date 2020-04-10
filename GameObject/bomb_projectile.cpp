#include "bomb_projectile.h"

BombProjectile::BombProjectile(const Projectile& other) : Projectile(other) {}

BombProjectile::BombProjectile(Size size, double speed, double effect_radius,
                               ProjectileType projectile_type)
    : Projectile(size, speed, projectile_type) {
  effect_radius_ = effect_radius;
}

void BombProjectile::Tick(int current_time) {
  Move();
}

bool BombProjectile::CheckForReceiveDamage(const Enemy& enemy) {
  return destination_.GetDistanceTo(enemy.GetPosition()).GetLength()
      <= effect_radius_ + kEpsilon;
}

#ifndef GAMEOBJECT_BOMB_PROJECTILE_H_
#define GAMEOBJECT_BOMB_PROJECTILE_H_

#include "projectile.h"

class BombProjectile : public Projectile {
 public:
  explicit BombProjectile(const Projectile& other);
  explicit BombProjectile(Size size, double speed, double effect_radius,
                          ProjectileType projectile_type =
                          ProjectileType::kBomb);
  void Tick(int current_time) override;
  bool CheckForReceiveDamage(const Enemy& enemy) override;
};

#endif  // GAMEOBJECT_BOMB_PROJECTILE_H_

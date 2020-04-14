#ifndef GAMEOBJECT_BOMB_PROJECTILE_H_
#define GAMEOBJECT_BOMB_PROJECTILE_H_

#include "projectile.h"

class BombProjectile : public Projectile {
 public:
  explicit BombProjectile(const Projectile& other);
  explicit BombProjectile(Size size, double speed, double effect_radius,
                          double up_force, ProjectileType projectile_type =
  ProjectileType::kBomb);
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
  void Tick(int current_time) override;
 private:
  double additional_draw_height_;
};

#endif  // GAMEOBJECT_BOMB_PROJECTILE_H_

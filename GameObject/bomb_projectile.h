#ifndef GAMEOBJECT_BOMB_PROJECTILE_H_
#define GAMEOBJECT_BOMB_PROJECTILE_H_

#include "abstract_projectile.h"

class BombProjectile : public AbstractProjectile {
 public:
  explicit BombProjectile(const AbstractProjectile& other);
  explicit BombProjectile(Size size, double speed,double effect_radius,
      double up_force, ProjectileType projectile_type =ProjectileType::kBomb);
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
  void Tick(int current_time) override;

 private:
  double additional_draw_height_ = 0;
};

#endif  // GAMEOBJECT_BOMB_PROJECTILE_H_

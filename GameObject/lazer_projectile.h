#ifndef GAMEOBJECT_LAZER_PROJECTILE_H
#define GAMEOBJECT_LAZER_PROJECTILE_H

#include "projectile.h"
#include "QPen"

class LazerProjectile : public Projectile {
 public:
  explicit LazerProjectile(const Projectile& other);
  explicit LazerProjectile(Size size, double speed,
      ProjectileType projectile_type = ProjectileType::kLazer);

  void Draw(QPainter* painter, const SizeHandler& handler) const override;
  void Tick(int current_time) override;

 private:
  Coordinate start_position_ = {0, 0};
};

#endif  // GAMEOBJECT_LAZER_PROJECTILE_H

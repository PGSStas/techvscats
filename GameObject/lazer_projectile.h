#ifndef GAMEOBJECT_LAZER_PROJECTILE_H_
#define GAMEOBJECT_LAZER_PROJECTILE_H_

#include "projectile.h"
#include "QPen"

class LazerProjectile : public Projectile {
 public:
  explicit LazerProjectile(const Projectile& other);
  explicit LazerProjectile(Size size,
        ProjectileType projectile_type = ProjectileType::kLazer);

  void Draw(QPainter* painter, const SizeHandler& handler) const override;
  void Tick(int current_time) override;

};

#endif  // GAMEOBJECT_LAZER_PROJECTILE_H_

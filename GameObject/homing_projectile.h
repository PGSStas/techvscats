#ifndef GAMEOBJECT_HOMING_PROJECTILE_H_
#define GAMEOBJECT_HOMING_PROJECTILE_H_

#include "abstract_projectile.h"

class HomingProjectile : public AbstractProjectile {
 public:
  HomingProjectile(Size size, double speed);
  HomingProjectile(const HomingProjectile& other) = default;
  ~HomingProjectile() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
};

#endif  // GAMEOBJECT_HOMING_PROJECTILE_H_

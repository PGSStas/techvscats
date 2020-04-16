#ifndef GAMEOBJECT_AIMED_PROJECTILE_H_
#define GAMEOBJECT_AIMED_PROJECTILE_H_

#include "abstract_projectile.h"

class AimedProjectile : public AbstractProjectile {
 public:
  AimedProjectile(Size size, double speed);
  AimedProjectile(const AimedProjectile& other) = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
};

#endif  // GAMEOBJECT_AIMED_PROJECTILE_H_

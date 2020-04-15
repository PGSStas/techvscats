#ifndef GAMEOBJECT_AIMED_PROJECTILE_H_
#define GAMEOBJECT_AIMED_PROJECTILE_H_

#include "abstract_projectile.h"

class AimedProjectile : public AbstractProjectile {
 public:
  explicit AimedProjectile(const AimedProjectile& other);
  explicit AimedProjectile(Size size, double speed);

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
};

#endif  // GAMEOBJECT_AIMED_PROJECTILE_H_

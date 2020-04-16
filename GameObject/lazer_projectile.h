#ifndef GAMEOBJECT_LAZER_PROJECTILE_H_
#define GAMEOBJECT_LAZER_PROJECTILE_H_

#include <QPen>

#include  <memory>

#include "abstract_projectile.h"

class LazerProjectile : public AbstractProjectile {
 public:
  explicit LazerProjectile(Size size);
  LazerProjectile(const LazerProjectile& other) = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
};

#endif  // GAMEOBJECT_LAZER_PROJECTILE_H_

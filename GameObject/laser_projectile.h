#ifndef GAMEOBJECT_LASER_PROJECTILE_H_
#define GAMEOBJECT_LASER_PROJECTILE_H_

#include <QPen>

#include  <memory>

#include "abstract_projectile.h"

class LaserProjectile : public AbstractProjectile {
 public:
  explicit LaserProjectile(Size size);
  LaserProjectile(const LaserProjectile& other) = default;
  virtual ~LaserProjectile() = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
};

#endif  // GAMEOBJECT_LASER_PROJECTILE_H_

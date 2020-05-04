#ifndef GAMEOBJECT_ABSTRACT_PROJECTILE_H_
#define GAMEOBJECT_ABSTRACT_PROJECTILE_H_

#include <memory>
#include <utility>

#include "enemy.h"
enum ProjectileType {
  kAimedProjectile,
  kBombProjectile,
  kLaserProjectile
};

class AbstractProjectile : public MovingObject {
 public:
  AbstractProjectile(Size size, double speed);
  AbstractProjectile(const AbstractProjectile& other);
  ~AbstractProjectile() override = default;

  void Move() override;

  virtual void SetParameters(const std::shared_ptr<Enemy>& aim,
                             Coordinate position, double speed_coefficient,
                             double damage);

  double GetDamage() const;
  virtual bool IsInAffectedArea(const Enemy& enemy);
  virtual ProjectileType GetProjectileType();

 protected:
  std::shared_ptr<Enemy> aim_ = {};
  double damage_ = 0;

  ProjectileType projectile_type;
};

#endif  // GAMEOBJECT_ABSTRACT_PROJECTILE_H_

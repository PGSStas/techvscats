#ifndef GAMEOBJECT_AIMED_PROJECTILE_H_
#define GAMEOBJECT_AIMED_PROJECTILE_H_

#include "abstract_projectile.h"

class AimedProjectile : public AbstractProjectile {
 public:
  AimedProjectile(Size size, double speed);
  AimedProjectile(const AimedProjectile& other) = default;
  ~AimedProjectile() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
 private:
  ProjectileType projectile_type = ProjectileType::kAimedProjectile;
};

#endif  // GAMEOBJECT_AIMED_PROJECTILE_H_

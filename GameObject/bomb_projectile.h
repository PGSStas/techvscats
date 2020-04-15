#ifndef GAMEOBJECT_BOMB_PROJECTILE_H_
#define GAMEOBJECT_BOMB_PROJECTILE_H_

#include "abstract_projectile.h"

class BombProjectile : public AbstractProjectile {
 public:
  BombProjectile(const BombProjectile& other);
  explicit BombProjectile(Size size, double speed, double effect_radius,
                          double up_force);

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;

  void SetParameters(Coordinate position, double speed_coefficient,
                     double damage,
                     const std::shared_ptr<Enemy>& aim) override;
  bool IsInAffectedArea(const Enemy& enemy) override;

 private:
  double effect_radius_ = 0;
  double up_force_ = 0;
  Coordinate start_position_ = {0, 0};
  double additional_draw_height_ = 0;
};

#endif  // GAMEOBJECT_BOMB_PROJECTILE_H_

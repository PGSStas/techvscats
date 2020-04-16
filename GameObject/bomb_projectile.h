#ifndef GAMEOBJECT_BOMB_PROJECTILE_H_
#define GAMEOBJECT_BOMB_PROJECTILE_H_

#include <memory>

#include "abstract_projectile.h"

class BombProjectile : public AbstractProjectile {
 public:
  BombProjectile(const BombProjectile& other);
  explicit BombProjectile(Size size, double speed, double effect_radius,
                          double up_force);
  virtual ~BombProjectile() = default;


  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;

  void SetParameters(const std::shared_ptr<Enemy>& aim, Coordinate position,
                     double speed_coefficient, double damage) override;
  bool IsInAffectedArea(const Enemy& enemy) override;

 private:
  double effect_radius_;
  double up_force_;
  Coordinate start_position_;
  double additional_draw_height_ = 0;
};

#endif  // GAMEOBJECT_BOMB_PROJECTILE_H_

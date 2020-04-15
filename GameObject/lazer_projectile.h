#ifndef GAMEOBJECT_LAZER_PROJECTILE_H_
#define GAMEOBJECT_LAZER_PROJECTILE_H_

#include "abstract_projectile.h"
#include "QPen"

class LazerProjectile : public AbstractProjectile {
 public:
  explicit LazerProjectile(const LazerProjectile& other);
  explicit LazerProjectile(Size size);

  void SetParameters(Coordinate position, double speed_coefficient, double damage,
                             const std::shared_ptr<Enemy>& aim) override ;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
  void Tick(int current_time) override;

 private:
  Coordinate start_position_ = {0, 0};
};

#endif  // GAMEOBJECT_LAZER_PROJECTILE_H_

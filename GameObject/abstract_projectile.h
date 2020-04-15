#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include <memory>
#include <utility>

#include "enemy.h"

class AbstractProjectile : public MovingObject {
 public:
  AbstractProjectile(const AbstractProjectile& other);
  explicit AbstractProjectile(Size size, double speed);

  void Move() override;

  virtual void SetParameters(Coordinate position, double speed_coefficient,
                             double damage, const std::shared_ptr<Enemy>& aim);
  void SetAnimationParameters(QColor draw_color, int iteration_time);

  double GetDamage() const;
  virtual bool IsInAffectedArea(const Enemy& enemy);

 protected:
  std::shared_ptr<Enemy> aim_ = {};
  double damage_ = 0;

  QColor draw_color_ = Qt::black;
  int iteration_time_ = 0;
};

#endif  // GAMEOBJECT_PROJECTILE_H_

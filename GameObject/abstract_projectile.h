#ifndef GAMEOBJECT_ABSTRACT_PROJECTILE_H_
#define GAMEOBJECT_ABSTRACT_PROJECTILE_H_

#include <memory>
#include <utility>

#include "View/particle_handler.h"
#include "enemy.h"

class AbstractProjectile : public MovingObject {
 public:
  AbstractProjectile(Size size, double speed);
  AbstractProjectile(const AbstractProjectile& other);
  ~AbstractProjectile() override = default;

  void Move() override;

  virtual void SetParameters(const std::shared_ptr<Enemy>& aim,
                             Coordinate position, double speed_coefficient,
                             double damage);
  void SetAnimationParameters(const QColor& draw_color, int iteration_time);

  double GetDamage() const;
  ParticleHandler* GetParticleHandler();
  virtual bool IsInAffectedArea(const Enemy& enemy);

 protected:
  ParticleHandler particle_handler;
  std::shared_ptr<Enemy> aim_ = {};
  double damage_ = 0;

  QColor draw_color_ = Qt::black;
  int iteration_time_ = 0;
};

#endif  // GAMEOBJECT_ABSTRACT_PROJECTILE_H_

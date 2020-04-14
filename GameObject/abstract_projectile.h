#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include <memory>

#include "enemy.h"

enum class ProjectileType {
  kDefault,
  kLazer,
  kBomb
};

class AbstractProjectile : public MovingObject {
 public:
  AbstractProjectile(const AbstractProjectile& other);

  virtual void SetParameters(Coordinate position, double speed, double damage,
                             std::shared_ptr<Enemy> aim);
  virtual void SetAnimationParameters(QColor draw_color, int iteration_time);

  ProjectileType GetType() const;
  double GetDamage() const;
  void Move() override;

  virtual bool IsInAffectedArea(const Enemy& enemy);

 protected:
  explicit AbstractProjectile(Size size, double speed,
                              ProjectileType projectile_type);

  ProjectileType type_ = ProjectileType::kDefault;
  std::shared_ptr<Enemy> aim_ = {};
  double damage_ = 0;

  QColor draw_color_ = Qt::black;
  int iteration_time_ = 0;

  // Fields for the child classes
  double up_force_ = 0;
  double effect_radius_ = 0;
  Coordinate start_position_;
};

#endif  // GAMEOBJECT_PROJECTILE_H_

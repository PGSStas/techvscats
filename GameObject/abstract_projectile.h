#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include <memory>
#include <utility>

#include "enemy.h"

enum class ProjectileType {
  kDefault,
  kLazer,
  kBomb
};
/////////////////////////////// sorted till here
class AbstractProjectile : public MovingObject {
 public:
  AbstractProjectile(const AbstractProjectile& other);
  explicit AbstractProjectile(Size size, double speed,
                              ProjectileType projectile_type,
                              double effect_radius = 0, double up_force = 0);

  void SetParameters(Coordinate position, double speed, double damage,
                    const std::shared_ptr<Enemy>& aim);
  void SetAnimationParameters(QColor draw_color, int iteration_time);

  ProjectileType GetType() const;
  bool IsInAffectedArea(const Enemy& enemy);
  double GetDamage() const;
  void Move() override;
 protected:
  ProjectileType type_;
  std::shared_ptr<Enemy> aim_ = {};
  double damage_ = 0;

  QColor draw_color_ = Qt::black;
  int iteration_time_ = 0;

  // Fields for the child classes
  double effect_radius_ = 0;
  double up_force_ = 0;
  Coordinate start_position_ = {0, 0};
};

#endif  // GAMEOBJECT_PROJECTILE_H_

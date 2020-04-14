#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include <memory>

#include "enemy.h"

enum class ProjectileType {
  kDefault,
  kLazer,
  kBomb
};

class Projectile : public MovingObject {
 public:
  Projectile(const Projectile& other);
  explicit Projectile(Size size, double speed,
                      ProjectileType projectile_type =
                      ProjectileType::kDefault);

  void SetParameters(double speed, double damage,
                     std::shared_ptr<Enemy> aim);
  void SetAnimationParameters(QColor draw_color, int iteration_time);

  ProjectileType GetType() const;
  double GetDamage() const;
  void Tick(int current_time) override;
  void Move() override;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
  virtual bool IsInAffectedArea(const Enemy& enemy);

 protected:
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

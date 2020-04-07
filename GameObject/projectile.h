#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include <memory>

#include "enemy.h"

enum class ProjectileType {
  kDefault
};

class Projectile : public MovingObject {
 public:
  explicit Projectile(const Projectile& other);
  explicit Projectile(Size size, double speed, double effect_radius = 0,
                      ProjectileType projectile_type = ProjectileType::kDefault);

  void SetParameters(double speed, int damage = 0,
                     std::shared_ptr<Enemy> aim = {});
  void SetAnimationParameters(QColor draw_color);
  double GetDamage() const;
  ProjectileType GetType() const;
  ~Projectile() = default;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
  void Tick(int current_time) override;
  void Move() override;
  bool IsUnderAttack(const Enemy& enemy) const;
  bool IsAimAchieved() const;

 protected:
  ProjectileType type_ = ProjectileType::kDefault;
  std::shared_ptr<Enemy> aim_ = {};
  bool is_aim_achieved_ = false;
  double effect_radius_ = 0;
  double damage_ = 0;
  QColor draw_color_ = Qt::darkYellow;
};

#endif  // GAMEOBJECT_PROJECTILE_H_

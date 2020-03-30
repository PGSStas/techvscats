#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include <memory>

#include "moving_object.h"

enum class ProjectileType {
  kDefault
};
// If the projectile reaches enemy, the controller will
// remove Projectile's object and cause damage damage to the enemy.
class Projectile : public MovingObject {
 public:
  explicit Projectile(const std::shared_ptr<Projectile>& other);
  explicit Projectile(int speed,
                      ProjectileType projectile_type = ProjectileType::kDefault);
  void SetParameters(int id, int damage, int speed,
                     std::shared_ptr<const GameObject> aim);
  void SetAnimationParameters(QColor draw_color,
                              int projectile_size);
  ~Projectile() = default;
  ProjectileType GetProjectileType() const;
  void Draw(QPainter* painter) const override;
  void Tick(int current_time) override;
  void Move() override;

 protected:
  QColor draw_color_ = Qt::darkYellow;
  int projectile_size_ = 1;
  std::shared_ptr<const GameObject> aim_;
  ProjectileType type_ = ProjectileType::kDefault;
  int id_ = 0;
  int type = 0;
  int damage_ = 0;
  bool is_aim_achived_ = false;
};

#endif  // GAMEOBJECT_PROJECTILE_H_

#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include <memory>

#include "enemy.h"

enum class ProjectileType {
  kDefault
};

class Projectile : public MovingObject {
 public:
  explicit Projectile(const std::shared_ptr<Projectile>& other);
  explicit Projectile(ProjectileType projectile_type = ProjectileType::kDefault);

  void SetParameters(int speed, int damage = 0,
                     std::shared_ptr<Enemy> aim = {});
  void SetAnimationParameters(QColor draw_color,
                              int projectile_size);
  ProjectileType GetType() const;
  ~Projectile() = default;
  void Draw(QPainter* painter) const override;
  void Tick(int current_time) override;
  void Move() override;

 protected:
  QColor draw_color_ = Qt::darkYellow;
  int projectile_size_ = 1;
  std::shared_ptr<Enemy> aim_ = {};
  ProjectileType type_ = ProjectileType::kDefault;
  int damage_ = 0;
  bool is_aim_achived_ = false;
};

#endif  // GAMEOBJECT_PROJECTILE_H_

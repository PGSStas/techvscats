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
  explicit Projectile(Size size, double speed ,
                      ProjectileType projectile_type = ProjectileType::kDefault);

  void SetParameters(double speed, int damage = 0,
                     std::shared_ptr<Enemy> aim = {});
  void SetAnimationParameters(QColor draw_color);
  ProjectileType GetType() const;
  ~Projectile() = default;
  void Draw(QPainter* painter, const SizeHandler& handler) const override;
  void Tick(int current_time) override;
  void Move() override;

 protected:
  QColor draw_color_ = Qt::darkYellow;
  std::shared_ptr<Enemy> aim_ = {};
  ProjectileType type_ = ProjectileType::kDefault;
  int damage_ = 0;
  bool is_aim_achived_ = false;
};

#endif  // GAMEOBJECT_PROJECTILE_H_

#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <memory>
#include <vector>
#include <list>
#include "enemy.h"
#include "projectile.h"

enum class Action {
  reload,
  before_fire,
  after_fire
};

class Building : public GameObject {
 public:
  explicit Building(const Building& other);
  Building(int id = 0, int settle_cost = 0, Size size = {20, 20},
           const std::list<std::shared_ptr<Enemy>>& enemies = {});

  void SetAnimationParameters(QColor reload_color, int reload_time,
                              QColor pre_color = Qt::black, int before_fire_time = 0,
                              QColor post_color = Qt::black, int after_fire_time = 0);

  void SetProjectile(int max_aims, int attack_range,
                     double attack_damage, int projectile_id);
  std::vector<Projectile> PrepareProjectiles(
      const Projectile& projectile_instance);

  void Tick(int current_time) override;
  void Draw(QPainter* painter,
            const SizeHandler& size_handler) const override;
  int GetId() const;
  int GetAttackRange() const;
  int GetProjectileId() const;
  bool IsInside(Coordinate point) const;
  bool IsReadyToCreateProjectiles() const;

 private:
  void UpdateAim();
  // parameters
  int id_ = 0;
  int settle_cost_ = 0;

  // action part
  Action action = Action::reload;
  int wait_time_ = 0;

  int action_time[3];
  // TODO(some body)  here should be imgs to draw
  QColor reload_color_ = QColor("black");
  QColor before_fire_color_ = QColor("black");
  QColor after_fire_color_ = QColor("black");

  int max_aims_ = 1;
  double attack_damage_ = 0;
  int attack_range_ = 0;
  int projectile_id_ = 0;
  bool is_ready_to_create_projectiles_ = false;
  bool is_possible_to_shoot = false;
  const std::list<std::shared_ptr<Enemy>>& enemies_;
  std::list<std::shared_ptr<Enemy>> aims_;

  const int kInteractionRadius = 15;
};

#endif  // GAMEOBJECT_BUILDING_H_

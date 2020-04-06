#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <memory>

#include "enemy.h"
#include "projectile.h"

enum class Action {
  reload,
  pre_fire,
  post_fire
};

class Building : public GameObject {
 public:
  Building(const std::list<std::shared_ptr<Enemy>>& enemies = {});
  explicit Building(const Building& other);
  void SetParameters(int id = 0,
                     int max_level = 0,
                     int settle_cost = 0,
                     int upgrade_cost = 0,
                     int max_aims = 0,
                     int attack_range = 0,
                     int attack_damage = 0,
                     int projectile_id = 0);

  void SetAnimationParameters(QColor wait_color,
                              int wait_time,
                              QColor pre_color = Qt::black,
                              int pre_fire_time = 0,
                              QColor post_color = Qt::black,
                              int post_fire_time = 0);

  virtual std::vector<Projectile> PrepareProjectiles(
      const Projectile& projectile_instance);
  virtual void Upgrade();

  void Tick(int controller_current_time) override;
  void Draw(QPainter* painter,
      const std::shared_ptr<SizeHandler>& size_handler) const override;

  bool IsInside(Coordinate point) const;

  int GetId() const;
  int GetAttackRange() const;
  int GetProjectileId() const;
  int GetMaxLevel() const;
  int GetCurrentLevel() const;
  bool IsReadyToCreateProjectile() const;

 protected:
  virtual void UpdateAim();
  // parameters
  int id_ = 0;
  int max_level_ = 0;
  int current_level_ = 0;
  int settle_cost_ = 0;
  int upgrade_cost_ = 0;
  int attack_range_ = 0;
  int attack_damage_ = 0;

  // action part
  Action action = Action::reload;
  int wait_time_ = 0;
  int reload_time_ = 0;
  int pre_fire_time_ = 0;
  int post_fire_time_ = 0;
  // later her should be imgs to draw
  QColor reload_color_ = QColor("black");
  QColor pre_fire_color_ = QColor("black");
  QColor post_fire_color_ = QColor("black");

  int max_aims_ = 1;
  const std::list<std::shared_ptr<Enemy>>& enemies_;
  int projectile_id_ = 0;
  bool is_ready_to_create_projectiles_ = false;
  bool have_possible_to_shoot_ = false;
  std::list<std::shared_ptr<Enemy>> aims_;

  const int kInteractionRadius = 15;
};

#endif  // GAMEOBJECT_BUILDING_H_

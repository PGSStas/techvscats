#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <memory>

#include "enemy.h"
#include "game_object.h"

enum class Action {
  reload,
  pre_fire,
  post_fire
};

class Building : public GameObject {
 public:
  explicit Building(const std::list<std::shared_ptr<Enemy>>& enemies,
                    int tower_type = 0);
  explicit Building(const std::shared_ptr<Building>& other);

  void SetParameters(int id,
                     int max_level = 0,
                     int settle_cost = 0,
                     int upgrade_cost = 0,
                     int action_range = 0,
                     int action_power = 0
  );

  void SetAnimationParameters(QColor wait_color,
                              int wait_time,
                              QColor pre_color = Qt::black,
                              int pre_fire_time = 0,
                              QColor post_color = Qt::black,
                              int post_fire_time = 0);

  virtual void Upgrade();

  void Tick(int controller_current_time) override;
  void Draw(QPainter* painter) const override;

  bool IsInside(Coordinate point) const;

  int GetId() const;
  int GetInteractionRadius() const;
  int GetTowerType() const;
  int GetMaxLevel() const;
  int GetCurrentLevel() const;

 protected:
  virtual void UpdateAim();
  virtual void DoAction();
  bool have_possible_to_shoot = false;
  std::shared_ptr<const Enemy> enemy_aim;
  // parameters
  int id_ = 0;
  int max_level_ = 0;
  int current_level_ = 0;
  int settle_cost_ = 0;
  int upgrade_cost_ = 0;
  int action_range_ = 0;
  int action_power_ = 0;
  int action_power_coefficient_ = 1;

  // action part
  Action action = Action::post_fire;
  int wait_time_ = 0;
  int reload_time_ = 0;
  int pre_fire_time_ = 0;
  int post_fire_time_ = 0;
  int action_time_coefficient_ = 1;
  // later her should be imgs to draw
  QColor reload_color_ = QColor("black");
  QColor pre_fire_color_ = QColor("black");
  QColor post_fire_color_ = QColor("black");

  std::shared_ptr<const Enemy> aim;

  const std::list<std::shared_ptr<Enemy>>& enemies_;
  const int kTowerType;
  const int kInteractionRadius = 15;
};

#endif  // GAMEOBJECT_BUILDING_H_

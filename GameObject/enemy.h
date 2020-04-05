#ifndef GAMEOBJECT_ENEMY_H_
#define GAMEOBJECT_ENEMY_H_

#include <memory>

#include "moving_object.h"
#include "Model/road.h"

class Enemy : public MovingObject {
 public:
  Enemy() = default;
  Enemy(const Enemy& enemy_instance);
  Enemy& operator=(const Enemy& enemy_instance);
  void Tick() override;

  void SetParameters(double speed);
  void Move() override;
  void Draw(QPainter* painter,
            const std::shared_ptr<SizeHandler>& size_handler) const override;
  void SetRoad(const Road& road);
  bool IsDead() const;

 private:
  double damage_ = 0;
  double armor_ = 0;
  int enemy_id_ = 0;
  int reward_ = 0;
  double current_health_ = 0;
  double max_health_ = 0;
  bool is_dead_ = false;

  std::shared_ptr<const Road> road_ = nullptr;
  int node_number_ = 0;
};

#endif  // GAMEOBJECT_ENEMY_H_

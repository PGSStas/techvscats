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
  void Tick(int current_time) override;

  void SetParameters(double speed);
  void Move() override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void SetRoad(const Road& road);
  void ReceiveDamage(double damage);

 private:
  double damage_ = 0;
  double armor_ = 0;
  int enemy_id_ = 0;
  int reward_ = 0;
  double current_health_ = 0;
  double max_health_ = 1;

  std::shared_ptr<const Road> road_ = nullptr;
  int node_number_ = 0;

  const int kMoveShift_ = 50;
};

#endif  // GAMEOBJECT_ENEMY_H_

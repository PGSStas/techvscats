#ifndef GAMEOBJECT_ENEMY_H_
#define GAMEOBJECT_ENEMY_H_

#include "moving_object.h"
#include "Model/road.h"
class Enemy : public MovingObject {
 public:
  Enemy() = default;
  explicit Enemy(Enemy* enemy_instance);
  Enemy& operator=(const Enemy& enemy_instance);

  void Tick(int current_time) override;
  void Draw(QPainter* painter) const override;
  void SetRoad(const Road& road);
  bool IsDead() const;
  void Move() override;

 private:
  double damage_ = 0;
  double armor_ = 0;
  int enemy_id_ = 0;
  int reward_ = 0;
  double current_health_ = 0;
  double max_health_ = 0;
  bool is_dead_ = 0;

  const Road* road_ = nullptr;
  int node_number_ = 0;
};

#endif  // GAMEOBJECT_ENEMY_H_

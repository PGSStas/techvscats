#ifndef GAMEOBJECT_ENEMY_H_
#define GAMEOBJECT_ENEMY_H_

#include "moving_object.h"
#include "Model/road.h"
class Enemy : public MovingObject {
 public:
  Enemy() = default;
  explicit Enemy(const Enemy* enemy_instance);
  void Tick() override;
  void Draw(QPainter* painter) const override;
  void SetRoad(const Road* road);
  bool IsDead() const;
 private:
  double damage_;
  double armor_;
  int enemy_id_;
  int reward_;
  double current_health_;
  double max_health_;
  bool is_dead_;

  const Road* road_;
  int node_number_;
};

#endif  // GAMEOBJECT_ENEMY_H_

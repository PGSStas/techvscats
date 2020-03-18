#ifndef CONTROLLER_ENEMY_H_
#define CONTROLLER_ENEMY_H_

#include "MovingObject.h"

class Enemy : public MovingObject {
 public:
  void Update() override;
  void Draw(QPainter*) override;
 private:
  double dealing_damage_{};
  double armor_{};  // Снижает получаемый урон
  int reward_{};
  double health_{};
  double max_health_{};
  // Road* my_road_;
  int direction_num{};  // чтобы из дороги достать следующую вершину

};

#endif  // CONTROLLER_ENEMY_H_

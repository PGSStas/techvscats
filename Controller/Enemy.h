#ifndef CONTROLLER_ENEMY_H_
#define CONTROLLER_ENEMY_H_

#include "MovingObject.h"

class Enemy : public MovingObject {
 public:
  void Update() override;
  void Draw(QPainter*) override;
  double dealing_damage{};
  double armor{};  // Снижает получаемый урон
  int bounty{};
  double health{};
  double maxHealth{};
  // Road* my_road;
  int direction_num{};  // чтобы из дороги достать следующую вершину
 private:
};

#endif  // CONTROLLER_ENEMY_H_

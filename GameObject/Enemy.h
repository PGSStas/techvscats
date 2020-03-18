#ifndef GAMEOBJECT_ENEMY_H_
#define GAMEOBJECT_ENEMY_H_

#include "MovingObject.h"

class Enemy : public MovingObject {
 public:
  void Tick() override;
  void Draw(QPainter* painter) override;

 private:
  double damage_dealing_;
  double armor_;  // Снижает получаемый урон
  int reward_;
  double health_;
  double max_health_;
  int direction_num;  // чтобы из дороги достать следующую вершину
};

#endif  // GAMEOBJECT_ENEMY_H_

#ifndef GAMEOBJECT_ENEMY_H_
#define GAMEOBJECT_ENEMY_H_

#include "MovingObject.h"

class Enemy : public MovingObject {
 public:
  void Tick() override;
  void Draw(QPainter* painter) override;

 private:
  double damage_dealing_;
  double armor_;
  int enemy_id_;
  int reward_;
  double current_health_;
  double max_health_;
  int node_number_;
};

#endif  // GAMEOBJECT_ENEMY_H_

#ifndef GAMEOBJECT_FAST_TOWER_H
#define GAMEOBJECT_FAST_TOWER_H

#include <QPainter>
#include "active_tower.h"

class FastTower : public ActiveTower {
 public:
  explicit FastTower(Coordinate pos);
  void Draw(QPainter* p, Coordinate pos) const override;
  void Tick() override;
  //FastTower* Copy() override;
};

#endif //GAMEOBJECT_FAST_TOWER_H

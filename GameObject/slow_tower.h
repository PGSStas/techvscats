#ifndef GAMEOBJECT_SLOW_TOWER_H
#define GAMEOBJECT_SLOW_TOWER_H

#include <QPainter>
#include "active_tower.h"

class SlowTower : public ActiveTower {
 public:
  explicit SlowTower(Coordinate pos);
  void Draw(QPainter* p, Coordinate pos) const override;
  void Tick() override;
};

#endif //GAMEOBJECT_SLOW_TOWER_H

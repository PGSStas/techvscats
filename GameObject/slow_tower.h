#ifndef GAMEOBJECT_SLOW_TOWER_H
#define GAMEOBJECT_SLOW_TOWER_H

#include <QPainter>

#include "active_tower.h"

// Just a class for tests. Doesn't do anything useful
// except drawing a red circle
class SlowTower : public ActiveTower {
 public:
  explicit SlowTower(Coordinate pos);
  void Draw(QPainter* p) const override;
  void Tick() override;
};

#endif //GAMEOBJECT_SLOW_TOWER_H

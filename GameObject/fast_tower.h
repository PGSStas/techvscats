#ifndef GAMEOBJECT_FAST_TOWER_H
#define GAMEOBJECT_FAST_TOWER_H

#include <QPainter>

#include "active_tower.h"

// Just a class for tests. Doesn't do anything useful
// except drawing a blue circle
class FastTower : public ActiveTower {
 public:
  explicit FastTower(Coordinate pos);
  void Draw(QPainter* p) const override;
  void Tick() override;
};

#endif //GAMEOBJECT_FAST_TOWER_H

#ifndef GAMEOBJECT_SLOW_TOWER_H_
#define GAMEOBJECT_SLOW_TOWER_H_

#include <QPainter>
#include <memory>

#include "active_tower.h"

// Just a class for tests. Doesn't do anything useful
// except drawing a red circle
class SlowTower : public ActiveTower {
 public:
  SlowTower(int id, Coordinate position);
  explicit SlowTower(const std::shared_ptr<Building>& other);

  void Draw(QPainter* painter) const override;
};

#endif  // GAMEOBJECT_SLOW_TOWER_H_

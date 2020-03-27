#ifndef GAMEOBJECT_FAST_TOWER_H_
#define GAMEOBJECT_FAST_TOWER_H_

#include <QPainter>

#include <memory>
#include "active_tower.h"

// Just a class for tests. Doesn't do anything useful
// except drawing a blue circle
class FastTower : public ActiveTower {
 public:
  FastTower(int id, Coordinate position);
  explicit FastTower(const std::shared_ptr<Building>& other);

  void Draw(QPainter* painter) const override;
};

#endif  // GAMEOBJECT_FAST_TOWER_H_

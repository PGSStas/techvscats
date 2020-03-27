#ifndef GAMEOBJECT_MULTI_TOWER_H_
#define GAMEOBJECT_MULTI_TOWER_H_

#include <QPainter>
#include <memory>

#include "active_tower.h"

// Just a class for tests. Doesn't do anything useful
// except drawing a red circle
class MultiTower : public ActiveTower {
 public:
  MultiTower();
  explicit MultiTower(const std::shared_ptr<Building>& other);
};

#endif  // GAMEOBJECT_MULTI_TOWER_H_

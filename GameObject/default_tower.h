#ifndef GAMEOBJECT_DEFAULT_TOWER_H_
#define GAMEOBJECT_DEFAULT_TOWER_H_

#include <QPainter>

#include <memory>
#include "active_tower.h"

// Just a class for tests. Doesn't do anything useful
// except drawing a blue circle
class DefaultTower : public ActiveTower {
 public:
  DefaultTower();
  explicit DefaultTower(const std::shared_ptr<Building>& other);
};

#endif  // GAMEOBJECT_DEFAULT_TOWER_H_

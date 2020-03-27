#ifndef GAMEOBJECT_ACTIVE_TOWER_H_
#define GAMEOBJECT_ACTIVE_TOWER_H_

#include <memory>
#include "building.h"

class ActiveTower : public Building {
 public:
  ActiveTower(int tower_type);
  explicit ActiveTower(const std::shared_ptr<Building>& other);
};

#endif  // GAMEOBJECT_ACTIVE_TOWER_H_

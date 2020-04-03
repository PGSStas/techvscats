#ifndef GAMEOBJECT_ACTIVE_TOWER_H_
#define GAMEOBJECT_ACTIVE_TOWER_H_

#include <memory>
#include "building.h"

class ActiveTower : public Building {
 public:
  explicit ActiveTower(int tower_type);
  explicit ActiveTower(const Building& other);
};

#endif  // GAMEOBJECT_ACTIVE_TOWER_H_

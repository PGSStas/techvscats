#ifndef GAMEOBJECT_ACTIVE_TOWER_H_
#define GAMEOBJECT_ACTIVE_TOWER_H_

#include <memory>
#include "building.h"

class ActiveTower : public Building {
 public:
  explicit ActiveTower(const std::list<std::shared_ptr<Enemy>>& enemies,int tower_type);
  explicit ActiveTower(const std::shared_ptr<Building>& other);
};

#endif  // GAMEOBJECT_ACTIVE_TOWER_H_

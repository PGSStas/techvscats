#ifndef GAMEOBJECT_ACTIVE_TOWER_H_
#define GAMEOBJECT_ACTIVE_TOWER_H_

#include "building.h"

class ActiveTower : public Building {
 public:
  ActiveTower(int tower_type, int id, Coordinate position);
  ActiveTower(std::shared_ptr<Building> other);
};

#endif  // GAMEOBJECT_ACTIVE_TOWER_H_

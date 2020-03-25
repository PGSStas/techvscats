#ifndef GAMEOBJECT_ACTIVE_TOWER_H_
#define GAMEOBJECT_ACTIVE_TOWER_H_

#include "building.h"

class ActiveTower : public Building {
 public:
  ActiveTower(int id, Coordinate pos);
  explicit ActiveTower(int id);
};

#endif  // GAMEOBJECT_ACTIVE_TOWER_H_

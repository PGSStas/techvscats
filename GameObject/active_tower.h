#ifndef GAMEOBJECT_ACTIVE_TOWER_H_
#define GAMEOBJECT_ACTIVE_TOWER_H_

#include "building.h"

class ActiveTower : public Building {
 public:
  ActiveTower(int id, Coordinate pos);
};

#endif  // GAMEOBJECT_ACTIVE_TOWER_H_

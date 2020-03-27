#ifndef GAMEOBJECT_EMPTY_TOWER_H_
#define GAMEOBJECT_EMPTY_TOWER_H_

#include "building.h"

// Represents an empty place on which the player can build a tower
class EmptyTower : public Building {
 public:
  explicit EmptyTower(Coordinate position);
  EmptyTower(std::shared_ptr<Building> other);
};

#endif  // GAMEOBJECT_EMPTY_TOWER_H_

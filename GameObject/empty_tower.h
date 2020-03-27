#ifndef GAMEOBJECT_EMPTY_TOWER_H_
#define GAMEOBJECT_EMPTY_TOWER_H_

#include <memory>

#include "building.h"

// Represents an empty place on which the player can build a tower
class EmptyTower : public Building {
 public:
  explicit EmptyTower(Coordinate position);
  explicit EmptyTower(const std::shared_ptr<Building>& other);
};

#endif  // GAMEOBJECT_EMPTY_TOWER_H_

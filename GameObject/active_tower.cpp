#include "active_tower.h"

ActiveTower::ActiveTower(int tower_type, int id, Coordinate position) :
  Building(tower_type, id, position) {}

ActiveTower::ActiveTower(const std::shared_ptr<Building>& other) :
  Building(other) {}

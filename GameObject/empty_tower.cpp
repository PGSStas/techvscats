#include "empty_tower.h"

EmptyTower::EmptyTower(Coordinate position) : Building(0, 0, position) {}

EmptyTower::EmptyTower(const std::shared_ptr<Building>& other) :
  Building(other) {}

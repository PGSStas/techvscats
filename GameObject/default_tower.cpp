#include "default_tower.h"

DefaultTower::DefaultTower() :
  ActiveTower(1) {}

DefaultTower::DefaultTower(const std::shared_ptr<Building>& other) :
  ActiveTower(other) {}

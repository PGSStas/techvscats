  #include "multi_tower.h"

MultiTower::MultiTower() :
  ActiveTower(2) {}

MultiTower::MultiTower(const std::shared_ptr<Building>& other) :
  ActiveTower(other) {}

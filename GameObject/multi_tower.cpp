  #include "multi_tower.h"

MultiTower::MultiTower() :
  ActiveTower(2) {}

MultiTower::MultiTower(const Building& other) :
  ActiveTower(other) {}

  #include "multi_tower.h"

MultiTower::MultiTower(const std::list<std::shared_ptr<Enemy>>& enemies) :
  ActiveTower(enemies,2) {}

MultiTower::MultiTower(const std::shared_ptr<Building>& other) :
  ActiveTower(other) {}

#include "active_tower.h"

ActiveTower::ActiveTower(int tower_type) :
    Building(tower_type) {}

ActiveTower::ActiveTower(const std::shared_ptr<Building>& other) :
    Building(other) {}

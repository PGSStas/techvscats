#include "active_tower.h"

ActiveTower::ActiveTower(const std::list<std::shared_ptr<Enemy>>& enemies,
                         int tower_type) :
    Building(enemies, tower_type) {}

ActiveTower::ActiveTower(const std::shared_ptr<Building>& other) :
    Building(other) {}

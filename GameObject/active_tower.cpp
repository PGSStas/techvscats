#include "active_tower.h"

ActiveTower::ActiveTower(int tower_type) :
    Building(tower_type) {}

ActiveTower::ActiveTower(const Building& other) :
    Building(other) {}

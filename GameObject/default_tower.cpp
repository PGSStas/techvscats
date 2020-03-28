#include "default_tower.h"
#include "QDebug"
DefaultTower::DefaultTower(const std::list<std::shared_ptr<Enemy>>& enemies) :
    ActiveTower(enemies, 1) {}

DefaultTower::DefaultTower(const std::shared_ptr<Building>& other) :
    ActiveTower(other) {}

void DefaultTower::Tick() {

}

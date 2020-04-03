#include "default_tower.h"

DefaultTower::DefaultTower() :
  ActiveTower(1) {}

DefaultTower::DefaultTower(const Building& other) :
  ActiveTower(other) {}

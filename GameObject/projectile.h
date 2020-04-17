#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include <memory>

#include "moving_object.h"
#include "building.h"

// If the projectile reaches enemy, the controller will
// remove Projectile's object and cause damage damage to the enemy.
class Projectile : public MovingObject {
  Projectile() = default;
  ~Projectile() = default;
 private:
  const std::shared_ptr<GameObject> aim_;
  bool is_aim_achived_;
  int damage_;
};

#endif  // GAMEOBJECT_PROJECTILE_H_
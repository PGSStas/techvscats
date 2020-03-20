#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include <memory>

#include "MovingObject.h"
#include "Building.h"


// If the projectile reaches enemy, the controller will
// remove Projectile's object and deal damage to the enemy.
class Projectile : public MovingObject {
 private:
  std::shared_ptr<GameObject> aim_;
  bool is_aim_achived_;
  int damage_;
};

#endif  // GAMEOBJECT_PROJECTILE_H_

#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include "MovingObject.h"
#include "Building.h"

// if the projectile reaches enemy, the controller will
// remove this class and deal damage to the enemy.
class Projectile : public MovingObject {
 private:
  GameObject* aim_;
  bool is_aim_achived_;
  int damage_;
};

#endif  // GAMEOBJECT_PROJECTILE_H_

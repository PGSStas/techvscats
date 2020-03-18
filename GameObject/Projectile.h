#ifndef GAMEOBJECT_PROJECTILE_H_
#define GAMEOBJECT_PROJECTILE_H_

#include "MovingObject.h"
#include "Building.h"

// if Projectile achive aim enemy, than controller will
// remove this class and damage the enemy.
class Projectile : public MovingObject {
 private:
  GameObject* aim_;
  bool is_aim_achived_;
  int damage_;
};

#endif  // GAMEOBJECT_PROJECTILE_H_

#ifndef CONTROLLER_ABSTRACT_CONTROLLER_H_
#define CONTROLLER_ABSTRACT_CONTROLLER_H_

#include "GameObject/enemy.h"
#include "GameObject/active_tower.h"
#include "GameObject/passive_tower.h"
#include "GameObject/projectile.h"

// AbstractController is needed to avoid the problem with looping include
// All public methods of controller should also be written here
class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void StartGame(int level) = 0;
  virtual void Tick() = 0;
};

#endif  // CONTROLLER_ABSTRACT_CONTROLLER_H_

#ifndef CONTROLLER_ABSTRACTCONTROLLER_H_
#define CONTROLLER_ABSTRACTCONTROLLER_H_

// Include GameObjects, that Controller use
#include "GameObject/Enemy.h"
#include "GameObject/ActiveTower.h"
#include "GameObject/PassiveTower.h"
#include "GameObject/Projectile.h"

// AbstractController is needed to avoid the problem with looping include
// All public methods of controller should also be written here
class AbstractController {
 public:
  virtual ~AbstractController() = default;

  virtual void StartGame(int level) = 0;
  virtual void Tick() = 0;
};

#endif  // CONTROLLER_ABSTRACTCONTROLLER_H_

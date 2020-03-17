#ifndef CONTROLLER_ABSTRACTCONTROLLER_H_
#define CONTROLLER_ABSTRACTCONTROLLER_H_

#include "Enemy.h"

class AbstractController {
 public:
  virtual ~AbstractController() = default;
  virtual void StartGame(int lvl) = 0;
  virtual void Tick() = 0;
};

#endif  // CONTROLLER_ABSTRACTCONTROLLER_H_

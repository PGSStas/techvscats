#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "Enemy.h"

class AbstractController {
 public:
  virtual ~AbstractController() = default;
  virtual void StartGame(int lvl) = 0;
  virtual void Tick() = 0;
};

#endif //ABSTRACTCONTROLLER_H

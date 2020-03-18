#ifndef CONTROLLER_MOVINGOBJECT_H_
#define CONTROLLER_MOVINGOBJECT_H_

#include <utility>
#include "GameObject.h"

class MovingObject : public GameObject {
 protected:
  std::pair<double, double> destination;
  double speed;
  double speed_bonus;
};

#endif  // CONTROLLER_MOVINGOBJECT_H_

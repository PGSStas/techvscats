#ifndef CONTROLLER_MOVINGOBJECT_H_
#define CONTROLLER_MOVINGOBJECT_H_

#include <utility>
#include "GameObject.h"

class MovingObject : public GameObject {
 protected:
  std::pair<double, double> destination_;
  double speed_;
  double speed_bonus_;
};

#endif  // CONTROLLER_MOVINGOBJECT_H_

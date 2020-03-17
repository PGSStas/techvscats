#ifndef CONTROLLER_MOVINGOBJECT_H_
#define CONTROLLER_MOVINGOBJECT_H_

#include <utility>
#include "GameObject.h"

class MovingObject : public GameObject {
 public:
  std::pair<double, double> destination;
  double speed;
  double speed_bonus;
  // void Death();
  std::pair<double, double> position_;
 private:
};

#endif  // CONTROLLER_MOVINGOBJECT_H_

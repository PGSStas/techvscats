#ifndef MOVINGOBJECT_H_
#define MOVINGOBJECT_H_

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

#endif  // MOVINGOBJECT_H_

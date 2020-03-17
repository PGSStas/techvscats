#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <utility>
#include "gameobject.h"

class MovingObject : public GameObject {
 public:
  std::pair<double, double> destination;
  double speed;
  double speed_bonus;
  //void Death();
  std::pair<double, double> position_;
 private:
};
#endif //MOVINGOBJECT_H

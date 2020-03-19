#ifndef GAMEOBJECT_MOVINGOBJECT_H_
#define GAMEOBJECT_MOVINGOBJECT_H_

#include "GameObject.h"

class MovingObject : public GameObject {
 protected:
  Coordinate destination_;
  double speed_;
  double speed_bonus_;
};

#endif  // GAMEOBJECT_MOVINGOBJECT_H_

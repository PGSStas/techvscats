#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 protected:
  Coordinate destination_;
  double speed_;
  double speed_coefficient_;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_
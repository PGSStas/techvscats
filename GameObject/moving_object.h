#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 public:
  MovingObject() = default;

  // returns moving vector
  virtual void Move() = 0;
  void SetSpeedCoefficient(double speed_coefficient);
  bool HasReached() const;
  double GetSpeed() const;

 protected:
  bool has_reached_ = false;
  Size moving_vector_;
  Coordinate destination_;
  double speed_;
  double speed_coefficient_ = 1;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_

#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 public:
  double GetSpeed() const;
  bool IsDead() const;
  virtual void Move() = 0;
  bool HasReached() const;

 protected:
  Coordinate destination_;
  bool is_end_reached_ = false;
  bool is_dead_ = false;
  double speed_;
  double speed_coefficient_ = 1;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_

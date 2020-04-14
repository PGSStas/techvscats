#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 public:
  MovingObject() = default;
  explicit MovingObject(double speed);

  virtual void Move() = 0;
  bool IsEndReached() const;

 protected:
  bool is_end_reached_ = false;
  Coordinate destination_ = Coordinate(0, 0);
  double speed_;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_

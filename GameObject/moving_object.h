#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 public:
  MovingObject(Size size, double speed, Coordinate position = {0, 0},
               Coordinate destination = {0, 0});
  ~MovingObject() override = default;

  void MoveToDestination();
  virtual void Move() = 0;
  virtual bool IsDead() const;
  bool IsEndReached() const;
 protected:
  double speed_;
  Coordinate destination_;
  bool is_end_reached_ = false;
  bool is_dead_ = false;
  double speed_coefficient_ = 1;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_

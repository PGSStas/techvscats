#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 public:
  MovingObject() = default;
  MovingObject(const Coordinate& start_position, const Coordinate& destination,
               double speed, double speed_coefficient);

  virtual void Move() = 0;
  Coordinate GetDestination() const;

  void SetDestination(const Coordinate& destination);
  void SetSpeed(double speed);
  void SetHasReached(bool is_readned);

  bool HasReached() const;
  double GetSpeed() const;

 protected:
  bool has_reached_ = false;
  Coordinate destination_;
  double speed_;
  double speed_coefficient_ = 1;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_

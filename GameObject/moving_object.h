#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 public:
  virtual void Move() = 0;
  Coordinate GetDestination() const;

  void SetDestination(const Coordinate& destination);
  void SetSpeed(double speed);
  void SetIsReached(bool is_readned);

  bool GetIsReached() const;
  double GetSpeed() const;

 protected:
  bool is_reached_destination_ = false;
  Coordinate destination_;
  double speed_;
  double speed_coefficient_;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_

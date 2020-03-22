#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include <QDebug>
#include "game_object.h"

class MovingObject : public GameObject {
 public:
  virtual void Move() = 0;
  Coordinate GetDestination() const;
  void SetDestination(const Coordinate& destination);
  double GetSpeed() const;
  void SetSpeed(double speed);
  int GetLiveTime() const;
  void SetStartLiveTime(int current_time);
  void SetCurrentTime(int current_time);
  bool GetIsReached();
  void SetIsReached(bool is_readned);
 private:
  bool is_reached_destination_ = false;
  Coordinate destination_;
  double speed_;
  double speed_coefficient_;
  int start_live_time_;
  int current_time_;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_

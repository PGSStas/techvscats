#ifndef GAMEOBJECT_BASE_H
#define GAMEOBJECT_BASE_H

#include "game_object.h"

class Base {
 public:
  Base(double max_health);

  double GetCurrentHealthPoints() const;
  double GetMaxHealth() const;

  bool IsDead() const;

  void ReduceHealthPoints(double damage);

 private:
  double current_health_points_;
  double max_health_;
  bool is_dead_;
};

#endif // GAMEOBJECT_BASE_H

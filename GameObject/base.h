#ifndef GAMEOBJECT_BASE_H_
#define GAMEOBJECT_BASE_H_

#include "game_object.h"

class Base {
 public:
  explicit Base(double max_health);

  double GetCurrentHealth() const;
  double GetMaxHealth() const;

  bool IsDead() const;

  void DecreaseHealth(double damage);

 private:
  double current_health_;
  double max_health_;
  bool is_dead_;
};

#endif  // GAMEOBJECT_BASE_H_

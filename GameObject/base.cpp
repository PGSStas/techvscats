#include "base.h"

Base::Base(double max_health)
    : max_health_(max_health),
      is_dead_(false),
      current_health_points_(max_health) {}

bool Base::IsDead() const {
  return is_dead_;
}

void Base::ReduceHealthPoints(double damage) {
  current_health_points_ -= damage;
  if (current_health_points_ <= 0) {
    current_health_points_ = 0;
    is_dead_ = true;
  }
}

double Base::GetCurrentHealthPoints() const {
  return current_health_points_;
}

double Base::GetMaxHealth() const {
  return max_health_;
}

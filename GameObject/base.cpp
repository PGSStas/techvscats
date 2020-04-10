#include "base.h"

Base::Base(double max_health)
    : max_health_(max_health),
      is_dead_(false),
      current_health_(max_health) {}

bool Base::IsDead() const {
  return is_dead_;
}

void Base::DecreaseHealth(double damage) {
  current_health_ -= std::min(damage, current_health_);
  if (current_health_ == 0) {
    is_dead_ = true;
  }
}

double Base::GetCurrentHealth() const {
  return current_health_;
}

double Base::GetMaxHealth() const {
  return max_health_;
}

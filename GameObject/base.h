#ifndef GAMEOBJECT_BASE_H_
#define GAMEOBJECT_BASE_H_

#include <algorithm>
#include <memory>
#include <vector>
#include "game_object.h"

class Base : public GameObject {
 public:
  Base(double max_health, Coordinate position);

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;

  double GetCurrentHealth() const;
  double GetMaxHealth() const;
  bool IsDead() const;
  void DecreaseHealth(double damage);

 private:
  double regeneration_rate_ = 0.05;
  double max_health_;
  double current_health_;

  bool is_dead_ = false;

  static const Coordinate kHealthBarPosition;
  static const Size kBaseSize;
  static const Size kHealthBarSize;
};

#endif  // GAMEOBJECT_BASE_H_

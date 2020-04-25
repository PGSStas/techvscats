#ifndef GAMEOBJECT_BASE_H_
#define GAMEOBJECT_BASE_H_

#include <algorithm>
#include <memory>
#include <vector>
#include "game_object.h"

class Base : public GameObject {
 public:
  Base(Size size, Coordinate position, double max_health);
  ~Base() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void DecreaseHealth(double damage);

  double GetCurrentHealth() const;
  double GetMaxHealth() const;
  bool IsDead() const;

 private:
  double regeneration_rate_ = 0.05;
  double max_health_;
  double current_health_;

  bool is_dead_ = false;

  const Coordinate kHealthBarPosition = Coordinate(0, 1060);
  const Size kHealthBarSize = Size(1920, 20);
};

#endif  // GAMEOBJECT_BASE_H_

#ifndef GAMEOBJECT_BASE_H_
#define GAMEOBJECT_BASE_H_

#include <algorithm>
#include <memory>
#include <vector>
#include "game_object.h"

class Base : public GameObject {
 public:
  Base(int gold, Size size, Coordinate position, double max_health);
  ~Base() override = default;

  void Tick(int current_time) override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void DecreaseHealth(double damage);

  double GetCurrentHealth() const;
  double GetMaxHealth() const;
  int GetGold() const;
  Coordinate GetGoldPosition() const;

  void AddGoldAmount(int gold_amount);
  void SubtractGoldAmount(int gold_amount);

  bool IsDead() const;

 private:
  int gold_;
  double regeneration_rate_ = 0.05;
  double max_health_;
  double current_health_;

  bool is_dead_ = false;

  const Coordinate kHealthPosition = Coordinate(1700, 1000);
  const Coordinate kGoldPosition = Coordinate(1800, 1000);
  const double kFontSize = 22;
};

#endif  // GAMEOBJECT_BASE_H_

#ifndef GAMEOBJECT_BASE_H_
#define GAMEOBJECT_BASE_H_

#include <algorithm>
#include <memory>
#include <vector>
#include <QFontDatabase>
#include "game_object.h"

class Base : public GameObject {
 public:
  explicit Base(int gold = 0, double max_health = 0,
                Coordinate position = {0, 0});
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

  static const Size kBaseSize;
  static const Coordinate kHealthPosition;
  static const Size kHealthSize;
  static const Coordinate kGoldPosition;
  static const Size kGoldSize;
};

#endif  // GAMEOBJECT_BASE_H_

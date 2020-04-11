#ifndef GAMEOBJECT_BASE_H_
#define GAMEOBJECT_BASE_H_

#include <algorithm>
#include "game_object.h"

class Base : public GameObject {
 public:
  explicit Base(double max_health);

  Base& operator=(const Base& other);

  void Draw(QPainter* painter,
            const std::shared_ptr<SizeHandler>& size_handler) const override;
  void Tick() override;

  void SetPositions(const std::vector<Coordinate>& positions);
  double GetCurrentHealth() const;
  double GetMaxHealth() const;

  bool IsDead() const;

  void DecreaseHealth(double damage);

 private:
  double regeneration_rate_ = 0.05;
  double max_health_;
  double current_health_;
  std::vector<Coordinate> positions_;

  bool is_dead_;

  const Coordinate kHealthBarPosition = Coordinate(0, 1060);
  const Size kBaseSize = Size(50, 50);
  const Size kHealthBarSize = Size(1920, 20);
};

#endif  // GAMEOBJECT_BASE_H_

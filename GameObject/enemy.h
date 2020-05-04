#ifndef GAMEOBJECT_ENEMY_H_
#define GAMEOBJECT_ENEMY_H_

#include <algorithm>
#include <chrono>
#include <memory>
#include <random>

#include "auric_field.h"
#include "effect.h"
#include "moving_object.h"
#include "Model/road.h"

class Enemy : public MovingObject {
 public:
  Enemy(double speed, double damage,
        double armor, int reward, double max_health, Size size = {60, 60},
        AuricField auric_field = AuricField(-1, -1));
  Enemy(const Enemy& other);
  ~Enemy() override = default;

  void Tick(int current_time) override;
  void Move() override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void DrawHealthBar(QPainter* painter, const SizeHandler& size_handler) const;

  void SetRoad(const Road& road);

  const AuricField& GetAuricField() const;
  Effect* GetAppliedEffect();
  double GetDamage() const;
  Coordinate GetPredictPosition(double predict_power = 1) const;
  void ReceiveDamage(double damage);
  int ComputeReward() const;

 private:
  double damage_;
  double armor_;
  int reward_;
  double max_health_;
  double current_health_;

  AuricField auric_field_;
  Effect applied_effect_ = Effect(EffectTarget::kEnemy);
  std::shared_ptr<const Road> road_ = nullptr;
  int node_number_ = 0;

  static std::mt19937 random_generator_;

  const int kMoveShift = 25;
  const Size kHealthBarShift = {18, 24};
  const Size kHealthBar = {36, 5};

 private:
  Coordinate ShiftCoordinate(Coordinate coordinate) const;
};

#endif  // GAMEOBJECT_ENEMY_H_

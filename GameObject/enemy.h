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
        int priority = 1, AuricField auric_field = AuricField(-1, -1));
  Enemy(const Enemy& other);
  ~Enemy() override = default;

  void Tick(int current_time) override;
  void Move() override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void DrawHealthBar(QPainter* painter, const SizeHandler& size_handler) const;

  void SetRoad(const Road& road);
  void SetPosition(const Enemy& instance, bool go_back = false);

  const AuricField& GetAuricField() const;
  Effect* GetAppliedEffect();
  double GetDamage() const;
  int GetPriority() const;
  Coordinate GetPredictPosition(double predict_power = 1) const;
  void ReceiveDamage(double damage);
  int ComputeReward() const;

  // boss
  void SetBoss(bool is_boss);
  bool IsBoss() const;
  bool IsTimeToKill() const;

  void KillReload();
  double GetKillRadius() const;

 private:
  double damage_;
  double armor_;
  int reward_;
  double max_health_;
  double current_health_;

  // if priority_ is zero, towers will shoot the enemy out of turn.
  // the greater the priority, the lesser amount of attention the enemy gets.
  // for now priority is in [0; 4].
  int priority_;

  AuricField auric_field_;
  Effect applied_effect_ = Effect(EffectTarget::kEnemy);
  std::shared_ptr<const Road> road_ = nullptr;
  int node_number_ = 0;

  static std::mt19937 random_generator_;

  const int kMoveShift = 20;
  Size health_bar_shift_ = {18, 24};
  Size health_bar_size_ = {36, 5};

  // boss
  bool is_boss_ = false;
  const double tower_kill_radius_ = 500;
  const int kill_reload_ = 12000;
  int wait_to_kill_ = kill_reload_ / 3;

 private:
  void ShiftCoordinate(Coordinate* coordinate);
};

#endif  // GAMEOBJECT_ENEMY_H_

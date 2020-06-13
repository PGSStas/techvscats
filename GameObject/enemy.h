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

struct BreederAttitude {
  double speed_coefficient = 1;
  double armor_coefficient = 1;
  double damage_coefficient = 1;
  double size_coefficient = 1;
};

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
  void CopyPosition(const Enemy& instance, bool go_back = false);

  const AuricField& GetAuricField() const;
  Effect* GetAppliedEffect();
  double GetDamage() const;
  int GetPriority() const;
  Coordinate GetPredictPosition(double predict_power = 1) const;
  void ReceiveDamage(double damage);
  int ComputeReward() const;

  // Special powers
  void SetBigHealth(Size health_bar_size_attitude,
                    double health_bar_shift_attitude);

  void SetTowerKiller(double tower_kill_radius, int kill_reload);
  bool IsTowerKiller() const;
  bool IsTimeToKill() const;

  void SetBreeder(int times_to_breed, int count,
                  BreederAttitude breed_apply_effect);
  bool IsBreeder() const;

  void KillReload();
  double GetKillRadius() const;

  double GetNewEnemiesCount() const;
  void Breed();

  int GetBossMusicId();
  void SetBossMusicId(int music_id);

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

  // Special powers
  QColor front_health_color_ = Qt::green;
  QColor back_health_color_ = Qt::red;

  double tower_kill_radius_ = 0;
  int kill_reload_ = 0;
  int wait_to_kill_ = 0;

  int times_to_breed_ = 0;
  int new_enemies_count_ = 0;
  BreederAttitude breed_attitude_;

  int boss_music_id_ = -1;

 private:
  void ShiftCoordinate(Coordinate* coordinate);
};

#endif  // GAMEOBJECT_ENEMY_H_

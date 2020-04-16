#ifndef GAMEOBJECT_ENEMY_H_
#define GAMEOBJECT_ENEMY_H_

#include <memory>
#include <algorithm>
#include <chrono>
#include <random>

#include "Model/road.h"
#include "moving_object.h"
#include "effect.h"
#include "auric_field.h"

class Enemy : public MovingObject {
 public:
  Enemy(Size size, double speed, double damage,
        double armor, int reward, double max_health,
        AuricField auric_field = AuricField(-1, -1));
  Enemy(const Enemy& enemy_instance);

  void Tick(int current_time) override;
  void Move() override;
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;
  void DrawHealthBar(QPainter* painter, const SizeHandler& size_handler) const;

  void SetRoad(const Road& road);

  const AuricField& GetAuricField() const;
  Effect* GetAppliedEffect();
  double GetDamage() const;
  void ReceiveDamage(double damage);

 private:
  double damage_ = 0;
  double armor_ = 0;
  int reward_ = 0;
  double max_health_ = 2;
  double current_health_ = 0;

  AuricField auric_field_;
  Effect applied_effect_ = Effect(EffectTarget::kEnemy);
  std::shared_ptr<const Road> road_ = nullptr;
  int node_number_ = 0;

  static std::mt19937 random_generator_;

  const int kMoveShift = 25;
  const Size kHealthBarShift = {18, 24};
  const Size kHealthBar = {36, 5};
};

#endif  // GAMEOBJECT_ENEMY_H_

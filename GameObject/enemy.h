#ifndef GAMEOBJECT_ENEMY_H_
#define GAMEOBJECT_ENEMY_H_

#include <memory>
#include <algorithm>
#include "moving_object.h"
#include "effect.h"
#include "auric_field.h"
#include "Model/road.h"

class Enemy : public MovingObject {
 public:
  Enemy() = default;
  Enemy(const Enemy& enemy_instance);
  Enemy& operator=(const Enemy& enemy_instance);

  void Tick() override;
  void Move() override;
  void Draw(QPainter* painter,
            std::shared_ptr<SizeHandler> size_handler) const override;
  void DrawAuras(QPainter* painter,
                 std::shared_ptr<SizeHandler> size_handler) const;
  void DrawHealthBars(QPainter* painter,
                      std::shared_ptr<SizeHandler> size_handler) const;
  void DrawAurasIcons(QPainter* painter,
                      std::shared_ptr<SizeHandler> size_handler) const;

  void SetParameters(double damage,
                     double armor,
                     int reward,
                     double speed,
                     double max_health);
  void SetRoad(const Road& road);
  void SetAuricField(double radius, int effect_id);

  const AuricField& GetAuricField();
  double GetDamage();

  bool IsDead() const;
  bool IsInAuricField(const Coordinate& coordinate) const;

  void ResetEffect();
  void ReceiveDamage(double damage);
  void ApplyEffect(const Effect& effect);
  void ChangeAuricFieldOrigin();

 private:
  AuricField auric_field_;
  Effect effect_ = Effect(EffectTarget::kEnemies, 1, 1, 1, 1, 1);

  double damage_ = 0;
  double armor_ = 0;
  int reward_ = 0;
  double current_health_ = 0;
  double max_health_ = 0;
  bool is_dead_ = false;

  std::shared_ptr<const Road> road_ = nullptr;
  int node_number_ = 0;

 private:
  void DrawAuraIcon(double coefficient,
                    Coordinate* point,
                    Size size,
                    QPainter* painter) const;
};

#endif  // GAMEOBJECT_ENEMY_H_

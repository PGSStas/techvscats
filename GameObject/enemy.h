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
            const std::shared_ptr<SizeHandler>& size_handler) const override;
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

  AuricField* GetAuricField();
  Effect* GetEffect();
  double GetDamage() const;

  bool IsDead() const;

  void ReceiveDamage(double damage);

 private:
  AuricField auric_field_;
  Effect effect_;

  double damage_ = 0;
  double armor_ = 0;
  int reward_ = 0;
  double current_health_ = 0;
  double max_health_ = 0;
  bool is_dead_ = false;

  std::shared_ptr<const Road> road_ = nullptr;
  int node_number_ = 0;

  const int kMoveShift_ = 50;

 private:
  void DrawAuraIcon(double coefficient,
                    Coordinate* point,
                    Size size,
                    QPainter* painter) const;
};

#endif  // GAMEOBJECT_ENEMY_H_

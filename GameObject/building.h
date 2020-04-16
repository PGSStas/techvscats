#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <list>
#include <memory>
#include <vector>

#include "abstract_projectile.h"
#include "auric_field.h"
#include "effect.h"
#include "enemy.h"

enum class Action {
  kReload,
  kBeforeFire,
  fAfterFire
};

class Building : public GameObject {
 public:
  explicit Building(Size size = {20, 20}, int id = 0, int settle_cost = 0,
                    AuricField aura = AuricField(-1, -1));
  Building(const Building& other);

  void Tick(int current_time) override;
  void UpdateAim(const std::list<std::shared_ptr<Enemy>>& enemies);
  void Draw(QPainter* painter,
            const SizeHandler& size_handler) const override;

  void SetAnimationParameters(const QColor& reload_color,
                              int reload_time,
                              const QColor& pre_color = Qt::black,
                              int before_fire_time = 0,
                              const QColor& post_color = Qt::black,
                              int after_fire_time = 0);
  void SetProjectile(int projectile_id, double attack_damage, int attack_range,
                     int max_aims);
  void SetReadyToCreateProjectileToFalse();

  int GetId() const;
  int GetAttackRange() const;
  int GetProjectileId() const;
  double GetDamage() const;
  double GetProjectileSpeedCoefficient() const;
  Effect* GetAppliedEffect();
  const AuricField& GetAuricField() const;
  const std::list<std::shared_ptr<Enemy>>& GetAims() const;
  bool IsInside(Coordinate point) const;
  bool IsReadyToCreateProjectiles() const;

 private:
  AuricField auric_field_;
  Effect applied_effect_ = Effect(EffectTarget::kBuilding);

  int id_ = 0;
  int cost_ = 0;

  // action part
  Action action_ = Action::kReload;
  int wait_time_ = 0;

  int action_time[3] = {0, 0, 0};
  // TODO(some body)  here should be Images to draw
  QColor reload_color_ = QColor("black");
  QColor before_fire_color_ = QColor("black");
  QColor after_fire_color_ = QColor("black");

  int projectile_id_ = 0;
  int attack_range_ = 0;
  uint max_aims_ = 1;
  double attack_damage_ = 0;
  bool is_ready_to_create_projectiles_ = false;
  bool is_ready_to_shoot = false;
  std::list<std::shared_ptr<Enemy>> aims_;
};

#endif  // GAMEOBJECT_BUILDING_H_

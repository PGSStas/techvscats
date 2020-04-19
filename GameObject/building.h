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
  kReload = 0,
  kBeforeFire = 1,
  kAfterFire = 2
};

class Building : public GameObject {
 public:
  explicit Building(Size size = {20, 20}, int id = 0, int settle_cost = 0,
                    AuricField aura = AuricField(-1, -1));
  Building(const Building& other);
  ~Building() override = default;

  void Tick(int current_time) override;
  void UpdateAim(const std::list<std::shared_ptr<Enemy>>& enemies);
  void Draw(QPainter* painter,
            const SizeHandler& size_handler) const override;

  void SetAnimationParameters(const QColor& reload_color,
                              const QColor& pre_color ,
                              const QColor& post_color ,
                              const std::vector<int>& action_time);
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
  bool IsInAttackRange(Coordinate coordinate) const;

 private:
  AuricField auric_field_;
  Effect applied_effect_ = Effect(EffectTarget::kBuilding);

  int id_ = 0;
  int cost_ = 0;

  // action part
  Action action_ = Action::kReload;
  int wait_time_ = 0;

  std::vector<int> action_time_;
  // TODO(some body)  here should be Images to draw
  QColor reload_color_ = QColor("black");
  QColor before_fire_color_ = QColor("black");
  QColor after_fire_color_ = QColor("black");

  int projectile_id_ = 0;
  int attack_range_ = 0;
  uint max_aims_ = 1;
  double attack_damage_ = 0;
  bool is_ready_to_create_projectiles_ = false;
  bool is_ready_to_shoot_ = false;
  std::list<std::shared_ptr<Enemy>> aims_;
};

#endif  // GAMEOBJECT_BUILDING_H_

#ifndef GAMEOBJECT_BUILDING_H_
#define GAMEOBJECT_BUILDING_H_

#include <algorithm>
#include <list>
#include <memory>
#include <vector>

#include "abstract_projectile.h"
#include "auric_field.h"
#include "effect.h"
#include "enemy.h"

enum class Action {
  kWait = 0,
  kBeforeFire = 1,
  kAfterFire = 2
};

class Building : public GameObject {
 public:
  explicit Building(int id, int settle_cost, const AuricField& aura,
                    Size size = {150, 150});
  Building(const Building& other);
  ~Building() override = default;

  void Tick(int current_time) override;
  void UpdateAim(const std::list<std::shared_ptr<Enemy>>& enemies);
  void Draw(QPainter* painter, const SizeHandler& size_handler) const override;

  void SetProjectile(int projectile_id, double attack_damage, int attack_range,
                     int max_aims, Size shooting_anchor);
  void SetReadyToCreateProjectileToFalse();
  void SetTotalCost(int total_cost);
  void SetInfo(const QString& header, const QString& description);

  int GetId() const;
  int GetAttackRange() const;
  int GetProjectileId() const;
  double GetDamage() const;
  int GetCost() const;
  int GetTotalCost() const;

  const QString& GetHeader() const;
  const QString& GetDescription() const;
  uint32_t GetMaxAims() const;
  double GetProjectileSpeedCoefficient() const;
  Effect* GetAppliedEffect();
  const AuricField& GetAuricField() const;
  const std::list<std::shared_ptr<Enemy>>& GetAims() const;
  Size GetShootingAnchor() const;

  bool IsInside(Coordinate point) const;
  bool IsReadyToCreateProjectiles() const;
  bool IsInAttackRange(Coordinate coordinate) const;

 private:
  AuricField auric_field_;
  Effect applied_effect_ = Effect(EffectTarget::kBuilding);

  int id_ = 0;
  int cost_ = 0;
  int total_cost_ = 0;

  // action part
  Action action_ = Action::kWait;
  int wait_time_ = 0;

  int projectile_id_ = 0;
  int attack_range_ = 0;
  uint32_t max_aims_ = 1;
  double attack_damage_ = 0;
  Size shooting_anchor_ = {0, 0};
  bool is_ready_to_create_projectiles_ = false;
  bool is_ready_to_shoot_ = false;
  std::list<std::shared_ptr<Enemy>> aims_;

  QString header_;
  QString description_;
};

#endif  // GAMEOBJECT_BUILDING_H_

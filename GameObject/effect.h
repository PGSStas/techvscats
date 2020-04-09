#ifndef GAMEOBJECT_EFFECT_H_
#define GAMEOBJECT_EFFECT_H_

#include <QPainter>
#include <View/size_handler.h>

enum class EffectTarget {
  kAll = 0,
  kEnemies = 1,
  kBuildings = 2
};

struct Effect {
  explicit Effect(EffectTarget effect_type,
                  double speed_coefficient = 1,
                  double armor_coefficient = 1,
                  double damage_coefficient = 1,
                  double attack_rate_coefficient = 1,
                  double range_coefficient = 1);

  void DrawEffectsIcons(QPainter* painter,
                        std::shared_ptr<SizeHandler> size_handler,
                        Coordinate position) const;

  void SumEffects(const Effect& other);
  void ResetEffect();

  EffectTarget GetEffectTarget() const;
  double GetSpeedCoefficient() const;
  double GetArmorCoefficient() const;
  double GetDamageCoefficient() const;
  double GetAttackRateCoefficient() const;
  double GetRangeCoefficient() const;

 private:
  EffectTarget effect_target_;
  double speed_coefficient_;
  double armor_coefficient_;
  double damage_coefficient_;
  double attack_rate_coefficient_;
  double range_coefficient_;

 private:
  void DrawEffectIcon(double coefficient,
                      Coordinate* point,
                      Size size,
                      QPainter* painter) const;
};

#endif  // GAMEOBJECT_EFFECT_H_

#ifndef GAMEOBJECT_EFFECT_H_
#define GAMEOBJECT_EFFECT_H_

#include <memory>
#include <algorithm>
#include <vector>
#include <QPainter>
#include "View/size_handler.h"

enum class EffectTarget {
  kAny = 0,
  kEnemy = 1,
  kBuilding = 2
};

enum class CoefficientType {
  kSpeed,
  kArmor,
  kDamage,
  kAttackRate,
  kRange
};

struct EffectVisualization {
  QColor reduced;
  QColor increased;
};

class Effect {
 public:
  explicit Effect(EffectTarget effect_type,
                  double speed_coefficient = 1,
                  double armor_coefficient = 1,
                  double damage_coefficient = 1,
                  double attack_rate_coefficient = 1,
                  double range_coefficient = 1);

  void DrawEffectsIcons(QPainter* painter,
                        const SizeHandler& size_handler,
                        Coordinate position) const;

  Effect& operator+=(const Effect& other);

  void ResetEffect();

  static void SetEffectVisualizations(
      const std::vector<EffectVisualization>& effect_visualization);

  EffectTarget GetEffectTarget() const;
  double GetSpeedCoefficient() const;
  double GetArmorCoefficient() const;
  double GetDamageCoefficient() const;
  double GetAttackRateCoefficient() const;
  double GetRangeCoefficient() const;

 private:
  EffectTarget effect_target_;
  std::vector<double> coefficients_;

  static std::vector<EffectVisualization> effect_visualizations_;

 private:
  void DrawEffectIcon(QPainter* painter,
                      Coordinate* point,
                      Size size,
                      CoefficientType coefficient_type) const;
};

#endif  // GAMEOBJECT_EFFECT_H_

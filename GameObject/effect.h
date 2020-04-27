#ifndef GAMEOBJECT_EFFECT_H_
#define GAMEOBJECT_EFFECT_H_

#include <algorithm>
#include <memory>
#include <vector>
#include <QPainter>

#include "Model/coordinate.h"
#include "Model/size.h"
#include "View/animation_player.h"
#include "View/size_handler.h"

enum class EffectTarget {
  kAny = 0,
  kEnemy = 1,
  kBuilding = 2
};

enum class CoefficientType {
  kMoveSpeed,
  kArmor,
  kDamage,
  kAttackRate,
  kRange,
};

struct EffectVisualization {
  AnimationPlayer reduced;
  AnimationPlayer increased;
};

class Effect {
 public:
  explicit Effect(EffectTarget effect_type,
                  double speed_coefficient = 1,
                  double armor_coefficient = 1,
                  double damage_coefficient = 1,
                  double attack_rate_coefficient = 1,
                  double range_coefficient = 1);

  void ResetEffect();
  void DrawEffectsIcons(QPainter* painter, const SizeHandler& size_handler,
                        Coordinate position, Size parent_size) const;

  static void SetEffectVisualizations(
      const std::vector<EffectVisualization>& effect_visualization);
  static void Rescale(Size size);
  static Size GetSize();

  EffectTarget GetEffectTarget() const;
  double GetMoveSpeedCoefficient() const;
  double GetArmorCoefficient() const;
  double GetDamageCoefficient() const;
  double GetAttackRateCoefficient() const;
  double GetRangeCoefficient() const;

  Effect& operator+=(const Effect& other);

 private:
  EffectTarget effect_target_;
  std::vector<double> coefficients_;
  static std::vector<EffectVisualization> effect_visualizations_;
  static const Size kSize;

 private:
  void DrawEffectIcon(QPainter* painter, Coordinate* point, Size size,
                      CoefficientType coefficient_type) const;
};

#endif  // GAMEOBJECT_EFFECT_H_

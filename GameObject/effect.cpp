#include "effect.h"

std::vector<EffectVisualization> Effect::effect_visualizations_{};

Effect::Effect(EffectTarget effect_type,
               double speed_coefficient,
               double armor_coefficient,
               double damage_coefficient,
               double attack_rate_coefficient,
               double range_coefficient)
    : effect_target_(effect_type), coefficients_(5) {
  coefficients_[static_cast<int>(CoefficientType::kSpeed)] = speed_coefficient;
  coefficients_[static_cast<int>(CoefficientType::kArmor)] = armor_coefficient;
  coefficients_[static_cast<int>(CoefficientType::kAttackRate)] =
      attack_rate_coefficient;
  coefficients_[static_cast<int>(CoefficientType::kDamage)] =
      damage_coefficient;
  coefficients_[static_cast<int>(CoefficientType::kRange)] = range_coefficient;
}

void Effect::ResetEffect() {
  int n = coefficients_.size();
  for (int i = 0; i < n; i++) {
    coefficients_[i] = 1;
  }
}

void Effect::DrawEffectsIcons(QPainter* painter,
                              const std::shared_ptr<SizeHandler>& size_handler,
                              Coordinate position) const {
  painter->save();

  painter->setBrush(Qt::red);
  Coordinate point =
      size_handler->GameToWindowCoordinate(position - Size(18, -18));
  Size size =
      size_handler->GameToWindowSize(Size(6, 6));

  DrawEffectIcon(painter, &point, size, CoefficientType::kDamage);

  if (effect_target_ == EffectTarget::kEnemy) {
    DrawEffectIcon(painter, &point, size, CoefficientType::kSpeed);
    DrawEffectIcon(painter, &point, size, CoefficientType::kArmor);
  }
  if (effect_target_ == EffectTarget::kBuilding) {
    DrawEffectIcon(painter, &point, size, CoefficientType::kRange);
    DrawEffectIcon(painter, &point, size, CoefficientType::kAttackRate);
  }

  painter->restore();
}

void Effect::DrawEffectIcon(QPainter* painter,
                            Coordinate* point,
                            Size size,
                            CoefficientType coefficient_type) const {
  int index = static_cast<int>(coefficient_type);
  double coefficient = coefficients_[index];
  if (std::abs(coefficient - 1) < kEpsilon) {
    return;
  }

  painter->save();

  EffectVisualization effect_visualization = effect_visualizations_[index];
  if (coefficient > 1) {
    painter->setBrush(effect_visualization.increased);
  } else if (coefficient < 1) {
    painter->setBrush(effect_visualization.reduced);
  }
  painter->drawEllipse(point->x, point->y, size.width, size.height);
  point->x += size.width + 1;

  painter->restore();
}

EffectTarget Effect::GetEffectTarget() const {
  return effect_target_;
}

double Effect::GetSpeedCoefficient() const {
  return coefficients_[static_cast<int>(CoefficientType::kSpeed)];
}

double Effect::GetArmorCoefficient() const {
  return coefficients_[static_cast<int>(CoefficientType::kArmor)];
}

double Effect::GetDamageCoefficient() const {
  return coefficients_[static_cast<int>(CoefficientType::kDamage)];
}

double Effect::GetAttackRateCoefficient() const {
  return coefficients_[static_cast<int>(CoefficientType::kAttackRate)];
}

double Effect::GetRangeCoefficient() const {
  return coefficients_[static_cast<int>(CoefficientType::kRange)];
}

void Effect::SetEffectVisualizations(
    const std::vector<EffectVisualization>& effect_visualization) {
  effect_visualizations_ = effect_visualization;
}

Effect& Effect::operator+=(const Effect& other) {
  int n = coefficients_.size();
  for (int i = 0; i < n; i++) {
    coefficients_[i] = std::max(coefficients_[i] + other.coefficients_[i], 0.0);
  }
  return *this;
}

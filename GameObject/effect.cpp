#include "effect.h"

std::vector<EffectVisualization> Effect::effect_visualizations_{};
const Size Effect::kSize = {30, 30};

Effect::Effect(EffectTarget effect_type,
               double speed_coefficient,
               double armor_coefficient,
               double damage_coefficient,
               double attack_rate_coefficient,
               double range_coefficient)
    : effect_target_(effect_type), coefficients_(5) {
  coefficients_[static_cast<int>(CoefficientType::kMoveSpeed)] =
      speed_coefficient;
  coefficients_[static_cast<int>(CoefficientType::kArmor)] =
      armor_coefficient;
  coefficients_[static_cast<int>(CoefficientType::kAttackRate)] =
      attack_rate_coefficient;
  coefficients_[static_cast<int>(CoefficientType::kDamage)] =
      damage_coefficient;
  coefficients_[static_cast<int>(CoefficientType::kRange)] =
      range_coefficient;
}

void Effect::ResetEffect() {
  std::fill(coefficients_.begin(), coefficients_.end(), 1.0);
}

void Effect::DrawEffectsIcons(QPainter* painter,
                              const SizeHandler& size_handler,
                              Coordinate position, Size parent_size) const {
  painter->save();
  painter->setBrush(Qt::red);
  Coordinate point =
      size_handler.GameToWindowCoordinate(
          position - Size(parent_size.width / 2 + 2,
                          -parent_size.height / 2 - 2));
  Size size = size_handler.GameToWindowSize(kSize);

  DrawEffectIcon(painter, &point, size, CoefficientType::kDamage);

  if (effect_target_ == EffectTarget::kEnemy) {
    DrawEffectIcon(painter, &point, size, CoefficientType::kMoveSpeed);
    DrawEffectIcon(painter, &point, size, CoefficientType::kArmor);
  }
  if (effect_target_ == EffectTarget::kBuilding) {
    DrawEffectIcon(painter, &point, size, CoefficientType::kAttackRate);
    DrawEffectIcon(painter, &point, size, CoefficientType::kRange);
  }
  painter->restore();
}

void Effect::SetEffectVisualizations(
    const std::vector<EffectVisualization>& effect_visualization) {
  effect_visualizations_ = effect_visualization;
}

void Effect::Rescale(Size size) {
  for (auto& effect_visualise : effect_visualizations_) {
    effect_visualise.increased.Rescale(size);
      effect_visualise.reduced.Rescale(size);
  }
}

Size Effect::GetSize() {
  return kSize;
}

EffectTarget Effect::GetEffectTarget() const {
  return effect_target_;
}

double Effect::GetMoveSpeedCoefficient() const {
  return coefficients_[static_cast<int>(CoefficientType::kMoveSpeed)];
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

Effect& Effect::operator+=(const Effect& other) {
  int n = coefficients_.size();
  for (int i = 0; i < n; i++) {
    coefficients_[i] = std::max(coefficients_[i] + other.coefficients_[i], 0.0);
  }
  return *this;
}
void Effect::DrawEffectIcon(QPainter* painter, Coordinate* point,
                            Size size, CoefficientType coefficient_type) const {
  int index = static_cast<int>(coefficient_type);
  double coefficient = coefficients_[index];
  if (std::abs(coefficient - 1) < constants::kEpsilon) {
    return;
  }

  painter->save();
  EffectVisualization effect_visualization = effect_visualizations_[index];
  if (coefficient > 1) {
    painter->drawImage(QPoint(point->x, point->y),
                       effect_visualization.increased.GetCurrentFrame());
  } else if (coefficient < 1) {
    painter->drawImage(QPoint(point->x, point->y),
                       effect_visualization.reduced.GetCurrentFrame());
  }
  point->x += size.width*0.6;
  painter->restore();
}

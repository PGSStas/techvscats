#include "effect.h"

Effect::Effect(EffectTarget effect_type,
               double speed_coefficient,
               double armor_coefficient,
               double damage_coefficient,
               double attack_rate_coefficient,
               double range_coefficient)
    : effect_target_(effect_type),
      speed_coefficient_(speed_coefficient),
      armor_coefficient_(armor_coefficient),
      damage_coefficient_(damage_coefficient),
      attack_rate_coefficient_(attack_rate_coefficient),
      range_coefficient_(range_coefficient) {}

void Effect::SumEffects(const Effect& other) {
  speed_coefficient_ += other.speed_coefficient_;
  armor_coefficient_ += other.armor_coefficient_;
  damage_coefficient_ += other.damage_coefficient_;
  attack_rate_coefficient_ += other.attack_rate_coefficient_;
  range_coefficient_ += other.range_coefficient_;
}

void Effect::ResetEffect() {
  speed_coefficient_ = 1;
  armor_coefficient_ = 1;
  damage_coefficient_ = 1;
  attack_rate_coefficient_ = 1;
  range_coefficient_ = 1;
}

void Effect::DrawEffectsIcons(QPainter* painter,
                              std::shared_ptr<SizeHandler> size_handler,
                              Coordinate position) const {
  painter->save();

  painter->setBrush(Qt::red);
  Coordinate point =
      size_handler->GameToWindowCoordinate(position - Size(18, -18));
  Size size =
      size_handler->GameToWindowSize(Size(6, 6));

  DrawEffectIcon(damage_coefficient_, &point, size, painter);

  if (effect_target_ == EffectTarget::kEnemies) {
    DrawEffectIcon(speed_coefficient_, &point, size, painter);
    DrawEffectIcon(armor_coefficient_, &point, size, painter);
  }
  if (effect_target_ == EffectTarget::kBuildings) {
    DrawEffectIcon(attack_rate_coefficient_, &point, size, painter);
    DrawEffectIcon(range_coefficient_, &point, size, painter);
  }

  painter->restore();
}

void Effect::DrawEffectIcon(double coefficient,
                            Coordinate* point,
                            Size size,
                            QPainter* painter) const {
  painter->save();

  if (coefficient > 1) {
    painter->setBrush(Qt::green);
    painter->drawEllipse(point->x, point->y, size.width, size.height);
    point->x += size.width + 1;
  } else if (coefficient < 1) {
    painter->setBrush(Qt::red);
    painter->drawEllipse(point->x, point->y, size.width, size.height);
    point->x += size.width + 1;
  }

  painter->restore();
}

EffectTarget Effect::GetEffectTarget() const {
  return effect_target_;
}

double Effect::GetSpeedCoefficient() const {
  return speed_coefficient_;
}

double Effect::GetArmorCoefficient() const {
  return armor_coefficient_;
}

double Effect::GetDamageCoefficient() const {
  return damage_coefficient_;
}

double Effect::GetAttackRateCoefficient() const {
  return attack_rate_coefficient_;
}

double Effect::GetRangeCoefficient() const {
  return range_coefficient_;
}

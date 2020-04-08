#include "effect.h"

Effect::Effect() : Effect(EffectTarget::kAll, 0, 0, 0, 0, 0) {}

Effect::Effect(EffectTarget effect_type,
               double speed_coefficient,
               double armor_coefficient,
               double damage_coefficient,
               double attack_rate_coefficient,
               double range_coefficient)
    : effect_target(effect_type),
      speed_coefficient(speed_coefficient),
      armor_coefficient(armor_coefficient),
      damage_coefficient(damage_coefficient),
      attack_rate_coefficient(attack_rate_coefficient),
      range_coefficient(range_coefficient) {}

void Effect::SumEffects(const Effect& other) {
  speed_coefficient += other.speed_coefficient;
  armor_coefficient += other.armor_coefficient;
  damage_coefficient += other.damage_coefficient;
  attack_rate_coefficient += other.attack_rate_coefficient;
  range_coefficient += other.range_coefficient;
}

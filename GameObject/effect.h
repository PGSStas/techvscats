#ifndef GAMEOBJECT_EFFECT_H_
#define GAMEOBJECT_EFFECT_H_

enum class EffectTarget {
  kAll = 0,
  kEnemies = 1,
  kBuildings = 2
};

struct Effect {
  EffectTarget effect_target;
  double speed_coefficient;
  double armor_coefficient;
  double damage_coefficient;
  double attack_rate_coefficient;
  double range_coefficient;

  Effect();
  Effect(EffectTarget effect_type,
         double speed_coefficient,
         double armor_coefficient,
         double damage_coefficient,
         double attack_rate_coefficient,
         double range_coefficient);

  void SumEffects(const Effect& other);
};

#endif  // GAMEOBJECT_EFFECT_H_

#ifndef MODEL_WAVE_H_
#define MODEL_WAVE_H_

#include <vector>
#include <utility>
#include "GameObject/enemy.h"

struct EnemyPack {
  Enemy enemy;
  int number;
};

struct Wave {  // to be updated
  int frequency;
  int road_count;
  EnemyPack enemies;
};

#endif  // MODEL_WAVE_H_

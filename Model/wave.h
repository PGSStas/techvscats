#ifndef MODEL_WAVE_H_
#define MODEL_WAVE_H_

#include <vector>
#include <utility>
#include "GameObject/enemy.h"

// Times in EnemyPack should be >0.
struct EnemyPack {
  Enemy enemy;
  int times;
};

struct Wave {  // to be updated
  int frequency;
  std::vector<EnemyPack> enemies;
};

#endif  // MODEL_WAVE_H_

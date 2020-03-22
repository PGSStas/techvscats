#ifndef MODEL_WAVE_H_
#define MODEL_WAVE_H_

#include <list>
#include <utility>
#include "GameObject/enemy.h"

// Times in EnemyPack should be >0.
struct EnemyPack {
  Enemy enemy;
  int times;
};

struct Wave {
  int frequency;
  std::list<EnemyPack> enemies;
};

#endif  // MODEL_WAVE_H_
